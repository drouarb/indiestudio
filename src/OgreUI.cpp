#include <OIS/OIS.h>
#include <iostream>
#include <stdlib.h>
#include "OgreUI.hh"

#ifdef OGRE_STATIC
  #include <OgreGLPlugin.h>
  #include <OgreParticleFXPlugin.h>
  #include <OgreBspSceneManagerPlugin.h>
  #include <OgrePCZPlugin.h>
  #include <OgreOctreePlugin.h>
  #include <OgreOctreeZonePlugin.h>
#endif

using namespace gauntlet;
using namespace core;

OgreUI::OgreUI(void)
	: mRoot(0),
	  mCamera(0),
	  mSceneMgr(0),
	  mWindow(0),
	  mResourcesCfg(Ogre::StringUtil::BLANK),
	  mPluginsCfg(Ogre::StringUtil::BLANK),
	  mTrayMgr(0),
	  mCameraMan(0),
	  mDetailsPanel(0),
	  mCursorWasVisible(true),
	  mShutDown(false),
	  mInputManager(0),
	  mMouse(0),
	  mKeyboard(0),
	  obs(NULL)
{
}

OgreUI::~OgreUI(void)
{
  if (mTrayMgr) delete mTrayMgr;
  if (mCameraMan) delete mCameraMan;
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
  delete mRoot;
}

bool OgreUI::configure(void)
{
  if (mRoot->showConfigDialog())
    {
      mWindow = mRoot->initialise(true, "Guantlet");
      return true;
    }
  else
    return false;
}


void OgreUI::chooseSceneManager(void)
{
  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
  mOverlaySystem = new Ogre::OverlaySystem();
  mSceneMgr->addRenderQueueListener(mOverlaySystem);
}

void OgreUI::createCamera(void)
{
  mCamera = mSceneMgr->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0, 0, 80));
  mCamera->lookAt(Ogre::Vector3(0, 0, -300));
  mCamera->setNearClipDistance(5);
  mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void OgreUI::createFrameListener(void)
{

  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;
  mWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  mInputManager = OIS::InputManager::createInputSystem(pl);
  mKeyboard = static_cast<OIS::Keyboard *>(mInputManager->createInputObject(
	  OIS::OISKeyboard, true));
  mMouse = static_cast<OIS::Mouse *>(mInputManager->createInputObject(
	  OIS::OISMouse, true));
  mMouse->setEventCallback(this);
  mKeyboard->setEventCallback(this);
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
  OgreBites::InputContext inputContext;
  inputContext.mMouse = mMouse;
  inputContext.mKeyboard = mKeyboard;
  mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow,
					   inputContext, this);
  mRoot->addFrameListener(this);
  mTrayMgr->setListener(this);
}

void OgreUI::destroyScene(void)
{
}

void OgreUI::createViewports(void)
{
  Ogre::Viewport *vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


void OgreUI::setupResources(void)
{
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		  archName, typeName, secName);
	}
    }
}

void OgreUI::createResourceListener(void)
{

}

void OgreUI::loadResources(void)
{
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool OgreUI::init()
{
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
  return (setup());
}

void OgreUI::go()
{
  mRoot->startRendering();
  destroyScene();
}

bool OgreUI::setup(void)
{
  mRoot = new Ogre::Root(mPluginsCfg);
#ifdef OGRE_STATIC
  mRoot->installPlugin(new Ogre::GLPlugin());
  mRoot->installPlugin(new Ogre::ParticleFXPlugin());
  mRoot->installPlugin(new Ogre::BspSceneManagerPlugin());
  mRoot->installPlugin(new Ogre::PCZPlugin());
  mRoot->installPlugin(new Ogre::OctreeZonePlugin());
  mRoot->installPlugin(new Ogre::OctreePlugin());
#endif
  setupResources();
  bool carryOn = configure();
  if (!carryOn) return false;
  chooseSceneManager();
  createCamera();
  createViewports();
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  createResourceListener();
  loadResources();
  initMap();
  createFrameListener();
  windowResized(mWindow);
  createScene();
  return true;
};

bool OgreUI::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  if (mWindow->isClosed())
    return false;

  if (mShutDown)
    return false;
  mKeyboard->capture();
  mMouse->capture();
  mTrayMgr->refreshCursor();
  mTrayMgr->frameRenderingQueued(evt);

  for (auto animation : this->animationsArray)
    {
      Ogre::AnimationState *t2 = animation.second;
      t2->addTime(evt.timeSinceLastFrame);
    }
  if (!mTrayMgr->isDialogVisible())
    {
      mCameraMan->frameRenderingQueued(evt);
    }

  return true;
}

bool OgreUI::keyPressed(const OIS::KeyEvent &arg)
{
  mCameraMan->injectKeyDown(arg);
  if (obs != NULL)
    if (keymap.count(arg.key) > 0)
      obs->keyDown(keymap[arg.key]);
  return true;
}

bool OgreUI::keyReleased(const OIS::KeyEvent &arg)
{
  mCameraMan->injectKeyUp(arg);
  if (obs != NULL)
    if (keymap.count(arg.key) > 0)
      obs->keyUp(keymap[arg.key]);
  return true;
}

bool OgreUI::mouseMoved(const OIS::MouseEvent &arg)
{
  mTrayMgr->injectMouseMove(arg);
  mCameraMan->injectMouseMove(arg);
  if (obs != NULL)
    obs->mouseMove(arg.state.X.rel, arg.state.Y.rel);
  return true;
}

bool OgreUI::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  mTrayMgr->injectMouseDown(arg, id);
  if (obs != NULL)
    if (mousemap.count(id) > 0)
      obs->keyDown(mousemap[id]);
  return true;
}

bool OgreUI::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  mTrayMgr->injectMouseUp(arg, id);
  if (obs != NULL)
    if (mousemap.count(id) > 0)
      obs->keyUp(mousemap[id]);
  return true;
}

void OgreUI::windowResized(Ogre::RenderWindow *rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

void OgreUI::windowClosed(Ogre::RenderWindow *rw)
{
  if (rw == mWindow)
    {
      if (mInputManager)
	{
	  mInputManager->destroyInputObject(mMouse);
	  mInputManager->destroyInputObject(mKeyboard);

	  OIS::InputManager::destroyInputSystem(mInputManager);
	  mInputManager = 0;
	}
    }
}

void OgreUI::buttonHit(OgreBites::Button *button)
{

  if (obs != NULL)
    {
      struct t_hitItem but;
      but.type = MenuItemType::BUTTON;
      obs->itemClick(std::atoi(button->getName().c_str()), but);
    }
}

void OgreUI::initMap()
{
  keymap[OIS::KC_UP] = IUIObserver::KEY_UP;
  keymap[OIS::KC_DOWN] = IUIObserver::KEY_DOWN;
  keymap[OIS::KC_RIGHT] = IUIObserver::KEY_RIGHT;
  keymap[OIS::KC_LEFT] = IUIObserver::KEY_LEFT;
  keymap[OIS::KC_ESCAPE] = IUIObserver::KEY_ESC;
  keymap[OIS::KC_TAB] = IUIObserver::KEY_TAB;
  keymap[OIS::KC_SPACE] = IUIObserver::KEY_SPACE;
  keymap[OIS::KC_BACK] = IUIObserver::KEY_BACK;
  keymap[OIS::KC_A] = IUIObserver::KEY_A;
  keymap[OIS::KC_B] = IUIObserver::KEY_B;
  keymap[OIS::KC_C] = IUIObserver::KEY_C;
  keymap[OIS::KC_D] = IUIObserver::KEY_D;
  keymap[OIS::KC_E] = IUIObserver::KEY_E;
  keymap[OIS::KC_F] = IUIObserver::KEY_F;
  keymap[OIS::KC_RETURN] = IUIObserver::KEY_ENTER;
  keymap[OIS::KC_G] = IUIObserver::KEY_G;
  keymap[OIS::KC_H] = IUIObserver::KEY_H;
  keymap[OIS::KC_I] = IUIObserver::KEY_I;
  keymap[OIS::KC_J] = IUIObserver::KEY_J;
  keymap[OIS::KC_K] = IUIObserver::KEY_K;
  keymap[OIS::KC_L] = IUIObserver::KEY_L;
  keymap[OIS::KC_M] = IUIObserver::KEY_M;
  keymap[OIS::KC_N] = IUIObserver::KEY_N;
  keymap[OIS::KC_O] = IUIObserver::KEY_O;
  keymap[OIS::KC_P] = IUIObserver::KEY_P;
  keymap[OIS::KC_Q] = IUIObserver::KEY_Q;
  keymap[OIS::KC_R] = IUIObserver::KEY_R;
  keymap[OIS::KC_S] = IUIObserver::KEY_S;
  keymap[OIS::KC_T] = IUIObserver::KEY_T;
  keymap[OIS::KC_U] = IUIObserver::KEY_U;
  keymap[OIS::KC_V] = IUIObserver::KEY_V;
  keymap[OIS::KC_W] = IUIObserver::KEY_W;
  keymap[OIS::KC_X] = IUIObserver::KEY_X;
  keymap[OIS::KC_Y] = IUIObserver::KEY_Y;
  keymap[OIS::KC_Z] = IUIObserver::KEY_Z;
  posmap[PCENTER] = OgreBites::TL_CENTER;
  posmap[PTOPRIGHT] = OgreBites::TL_TOPRIGHT;
  posmap[PTOPLEFT] = OgreBites::TL_TOPLEFT;
  posmap[PTOP] = OgreBites::TL_TOP;
  posmap[PBOTTOM] = OgreBites::TL_BOTTOM;
  posmap[PBOTTOMLEFT] = OgreBites::TL_BOTTOMLEFT;
  posmap[PBOTTOMRIGHT] = OgreBites::TL_BOTTOMRIGHT;
  posmap[PRIGHT] = OgreBites::TL_RIGHT;
  posmap[PLEFT] = OgreBites::TL_LEFT;
  mousemap[OIS::MB_Left] = IUIObserver::KEY_MOUSE1;
  mousemap[OIS::MB_Right] = IUIObserver::KEY_MOUSE2;
}

void OgreUI::remove(int id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->destroyWidget(ss.str());
}

void OgreUI::addButton(Position pos, int id, std::string text, int texture_id)
{

  std::stringstream ss;
  ss << id;
  OgreBites::Button *c = mTrayMgr->createButton(posmap[pos], ss.str(), text);

}


void OgreUI::setIObserver(gauntlet::core::IUIObserver *Obs)
{
  this->obs = Obs;
}

void OgreUI::loadSound(std::string &path)
{

}

void OgreUI::playSound(int id)
{

}

void OgreUI::checkBoxToggled(OgreBites::CheckBox *checkBox)
{
  if (obs != NULL)
    {
      struct t_hitItem Box;
      Box.type = MenuItemType::CHECKBOX;
      if (checkBox->isChecked())
	Box.state = MenuCheckBoxState::CHECKED;
      else
	Box.state = MenuCheckBoxState::NOCHECKED;
      obs->itemClick(std::atoi(checkBox->getName().c_str()), Box);
    }
}

void OgreUI::addCheckbox(gauntlet::core::Position pos, int id, std::string text,
			 int texture_id)
{

  std::stringstream ss;
  ss << id;
  mTrayMgr->createCheckBox(posmap[pos], ss.str(), text);
}

void OgreUI::addProgressBar(gauntlet::core::Position pos, int id,
			    std::string text, int texture_id, int value)
{
  std::stringstream ss;
  ss << id;
  OgreBites::ProgressBar *p = mTrayMgr->createProgressBar(posmap[pos], ss.str(),
							  text, 300, 10);
  p->setProgress(value);
}

void OgreUI::addSelectMenu(gauntlet::core::Position pos, int id,
			   std::string name, std::vector<std::string> &item,
			   int texture_id)
{
  std::stringstream ss;
  ss << id;
  OgreBites::SelectMenu *m = mTrayMgr->createLongSelectMenu(posmap[pos],
							    ss.str(), name, 200,
							    item.size());
  std::vector<std::string>::iterator it = item.begin();
  while (it != item.end())
    {
      m->addItem(*it);
      it++;
    }
}

void OgreUI::itemSelected(OgreBites::SelectMenu *menu)
{
  if (obs != NULL)
    {
      struct t_hitItem m;
      m.type = MenuItemType::SELECTMENU;
      m.data = menu->getSelectedItem();
      obs->itemClick(std::atoi(menu->getName().c_str()), m);
    }
}

void OgreUI::addSlideBar(gauntlet::core::Position pos, int id, std::string text,
			 int max, int texture_id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->createLongSlider(posmap[pos], ss.str(), text, 100, 100, 0, max,
			     100);
}

void OgreUI::sliderMoved(OgreBites::Slider *slider)
{
  if (obs != NULL)
    {
      struct t_hitItem m;
      m.type = MenuItemType::SLIDE;
      m.value = slider->getValue();
      obs->itemClick(std::atoi(slider->getName().c_str()), m);
    }
}

void OgreUI::updateItemValue(int itemid, struct t_hitItem item) {
    std::stringstream ss;
    ss << itemid;
    switch (item.type) {
        case MenuItemType::SLIDE: {
            OgreBites::Slider *s = static_cast<OgreBites::Slider *>(mTrayMgr->getWidget(ss.str()));
            s->setValue(item.value, true);
        }
            break;
            case MenuItemType::PROGRESSBAR: {
                OgreBites::ProgressBar *p = static_cast<OgreBites::ProgressBar *>(mTrayMgr->getWidget(ss.str()));
                p->setProgress(item.value);
            }
            break;
            case MenuItemType::TEXTBOX: {
            OgreBites::TextBox *t = static_cast<OgreBites::TextBox *>(mTrayMgr->getWidget(ss.str()));
            t->setCaption(item.data);
        }
            break;
        case MenuItemType::LABEL: {
            OgreBites::Label *label = static_cast<OgreBites::Label *>(mTrayMgr->getWidget(ss.str()));
            label->setCaption(item.data);
        }
            break;
    }
}

void OgreUI::addTextbox(gauntlet::core::Position pos, int id, std::string text,
			int texture_id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->createTextBox(posmap[pos], ss.str(), text, 100, 20);
}

void OgreUI::addLabel(gauntlet::core::Position pos, int id, std::string text,
		      int texture_id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->createLabel(posmap[pos], ss.str(), text);
}

void OgreUI::hideItem(int id)
{
  std::stringstream ss;
  ss << id;
  OgreBites::Widget *w = mTrayMgr->getWidget(ss.str());
  w->hide();
}

void OgreUI::createScene(void)
{
}

void OgreUI::quit()
{
  this->mShutDown = true;
}

void OgreUI::showItem(int id) {
    std::stringstream ss;
    ss << id;
    OgreBites::Widget *w =   mTrayMgr->getWidget(ss.str());
    w->show();
}




  pState->setLoop(loop);
  pState->setEnabled(true);
  this->animationsArray[pEntity->getName() +
			pState->getAnimationName()] = pState;
}

void OgreUI::stopAnimation(int animationId, int entityId)
{
  Ogre::Entity *pEntity = this->mSceneMgr->getEntity("" + entityId);
  Ogre::AnimationState *pState = pEntity->getAnimationState("");

  Ogre::AnimationState *&animation = this->animationsArray[pEntity->getName() +
							   pState->getAnimationName()];
  if (animation == NULL)
    return;
  animation->setTimePosition(0);
  animation->setEnabled(false);
  animation = NULL;
}