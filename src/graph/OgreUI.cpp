#include <OIS/OIS.h>
#include <iostream>
#include <stdlib.h>
#include "OgreUI.hh"
#include "Math.hh"

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
	  planNode(0),
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
      mWindow = mRoot->initialise(true, "Gauntlet");
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
  worldNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("World");
  planNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Plan");
}

void OgreUI::createCamera(void)
{

  mCamera = mSceneMgr->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0, 100, 80));
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
  if (mSceneMgr)
    {
      this->mSceneMgr->destroyAllAnimations();
      this->mSceneMgr->destroyAllEntities();
      this->mSceneMgr->destroyAllCameras();
      this->mSceneMgr->destroyAllLights();
      this->mSceneMgr->destroyAllParticleSystems();
    }
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
  mRoot->installPlugin(new OgreOggSound::OgreOggSoundPlugin());
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
  initSound();
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
      {
	obs->keyDown(keymap.at(arg.key));
      }
  return true;
}

bool OgreUI::keyReleased(const OIS::KeyEvent &arg)
{
  mCameraMan->injectKeyUp(arg);

  if (obs != NULL)
    if (keymap.count(arg.key) > 0)
      obs->keyUp(keymap.at(arg.key));
  return true;
}

bool OgreUI::mouseMoved(const OIS::MouseEvent &arg)
{
  mCameraMan->injectMouseMove(arg);
  mTrayMgr->injectMouseMove(arg);
  if (obs != NULL)
    obs->mouseMove(arg.state.X.abs, arg.state.Y.abs);
  return true;
}

bool OgreUI::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  mTrayMgr->injectMouseDown(arg, id);
  if (obs != NULL)
    if (mousemap.count(id) > 0)
      obs->keyDown(mousemap.at(id));
  return true;
}

bool OgreUI::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  mTrayMgr->injectMouseUp(arg, id);
  if (obs != NULL)
    if (mousemap.count(id) > 0)
      obs->keyUp(mousemap.at(id));
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

void OgreUI::removeItem(int id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->destroyWidget(ss.str());
}

void OgreUI::addButton(Position pos, int id, std::string text, int texture_id)
{

  std::stringstream ss;
  ss << id;
  OgreBites::Button *c = mTrayMgr->createButton(posmap.at(pos), ss.str(), text);

}


void OgreUI::setIObserver(gauntlet::core::IUIObserver *Obs)
{
  this->obs = Obs;
}

void OgreUI::loadSound(int id, const std::string &path)
{
  std::stringstream ss;
  ss << id;
  mSoundManager->createSound(ss.str(), path.c_str(), true, false, false);
}

void OgreUI::playSound(int id)
{
  std::stringstream ss;
  ss << id;
  mSoundManager->getSound(ss.str())->play();
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
  mTrayMgr->createCheckBox(posmap.at(pos), ss.str(), text);
}

void OgreUI::addProgressBar(gauntlet::core::Position pos, int id,
			    std::string text, int texture_id, int value)
{
  std::stringstream ss;
  ss << id;
  OgreBites::ProgressBar *p = mTrayMgr->createProgressBar(posmap.at(pos), ss.str(),
							  text, 300, 10);
  p->setProgress(value);
}

void OgreUI::addSelectMenu(gauntlet::core::Position pos, int id,
			   std::string name, std::vector<std::string> &item,
			   int texture_id)
{
  std::stringstream ss;
  ss << id;
  OgreBites::SelectMenu *m = mTrayMgr->createLongSelectMenu(posmap.at(pos),
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
  mTrayMgr->createLongSlider(posmap.at(pos), ss.str(), text, 100, 100, 0, max,
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

void OgreUI::updateItemValue(int itemid, struct t_hitItem item)
{
  std::stringstream ss;
  ss << itemid;
  switch (item.type)
    {
      case MenuItemType::SLIDE:
	{
	  OgreBites::Slider *s = static_cast<OgreBites::Slider *>(mTrayMgr->getWidget(
		  ss.str()));
	  s->setValue(item.value, true);
	}
      break;
      case MenuItemType::PROGRESSBAR:
	{
	  OgreBites::ProgressBar *p = static_cast<OgreBites::ProgressBar *>(mTrayMgr->getWidget(
		  ss.str()));
	  p->setProgress(item.value);
	}
      break;
      case MenuItemType::TEXTBOX:
	{
	  OgreBites::TextBox *t = static_cast<OgreBites::TextBox *>(mTrayMgr->getWidget(
		  ss.str()));
	  t->setText(item.data);
	}
      break;
      case MenuItemType::LABEL:
	{
	  OgreBites::Label *label = static_cast<OgreBites::Label *>(mTrayMgr->getWidget(
		  ss.str()));
	  label->setCaption(item.data);
	}
      break;
      case MenuItemType::CHECKBOX:
	{
	  OgreBites::CheckBox *c = static_cast<OgreBites::CheckBox *>(mTrayMgr->getWidget(
		  ss.str()));
	  if (item.state == CHECKED)
	    c->setChecked(true, true);
	  else
	    c->setChecked(false, true);
	}
      break;
    }
}

void OgreUI::addTextbox(gauntlet::core::Position pos, int id, std::string text,
			int texture_id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->createTextBox(posmap.at(pos), ss.str(), text, 300, 80);
}

void OgreUI::addLabel(gauntlet::core::Position pos, int id, std::string text,
		      int texture_id)
{
  std::stringstream ss;
  ss << id;
  mTrayMgr->createLabel(posmap.at(pos), ss.str(), text, text.size() * 12);
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
  showBackground();
  //TODO clean
  Ogre::Light *pLight = this->mSceneMgr->createLight();
  pLight->setType(Ogre::Light::LT_SPOTLIGHT);
  pLight->setDiffuseColour(Ogre::ColourValue::White);
  pLight->setPosition(0, 500, 0);
  pLight->setSpotlightRange(Ogre::Radian(0.0), Ogre::Radian(180.0));
  pLight->setPowerScale(400000.0);
  this->mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));
  this->mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  this->addWorldEntity(23, "draugr", 0, 0, 90, 0);
  //END TODO
  pointLight->setSpotlightInnerAngle(Ogre::Radian(0));
  pointLight->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(180)));
  pointLight->setDiffuseColour(Ogre::ColourValue::White);
  pointLight->setSpecularColour(Ogre::ColourValue::White);
  mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox");
  addMapEntity(1,TUDORHOUSE, 0, 0, 0,  TUDORHOUSE_M);
}

void OgreUI::quit()
{
  this->mShutDown = true;
}

void OgreUI::showItem(int id)
{
  std::stringstream ss;
  ss << id;
  OgreBites::Widget *w = mTrayMgr->getWidget(ss.str());
  w->show();
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

void OgreUI::playAnimation(int entityId, int animationId, bool loop)
{
  std::stringstream ss;

  ss << entityId;
  Ogre::Entity *pEntity = this->mSceneMgr->getEntity(ss.str());
  int nb = 0;

  Ogre::AnimationStateIterator mapIterator = pEntity->getAllAnimationStates()->getAnimationStateIterator();
  auto it = mapIterator.begin();
  while (it != mapIterator.end())
    {
      std::pair<const Ogre::String, Ogre::AnimationState *> &reference1 = *it;
      if (nb == entityId)
	{
	  this->playAnimation(entityId, reference1.first, loop);
	}
      it++;
      ++nb;
    }
}


void OgreUI::playAnimation(int entityId, std::string const &animationName,
			   bool loop)
{
  std::stringstream ss;

  ss << entityId;
  Ogre::Entity *pEntity = this->mSceneMgr->getEntity(ss.str());
  Ogre::AnimationState *pState = pEntity->getAnimationState(animationName);

  pState->setLoop(loop);
  pState->setEnabled(true);
  this->animationsArray[pEntity->getName() +
			pState->getAnimationName()] = pState;
}

std::pair<int, int> OgreUI::getSizeWindow()
{
  return (std::pair<int, int>(mWindow->getWidth(), mWindow->getHeight()));
}

void OgreUI::showBackground()
{
  mTrayMgr->showBackdrop("Ogre/Background");
}

void OgreUI::hideBackground()
{
  mTrayMgr->hideBackdrop();
}

void OgreUI::initSound()
{
  this->mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
  mSoundManager->init();
}

void OgreUI::stopSound(int id)
{
  std::stringstream ss;
  ss << id;
  mSoundManager->getSound(ss.str())->stop();
}

Ogre::SceneManager *OgreUI::getSceneManager()
{
  return this->mSceneMgr;
}


bool OgreUI::addWorldEntity(int entityId, EntityName meshid, int x, int y,
			    short angle, Texturename texture_id)
{
  std::stringstream ss;
  ss << entityId;
  Ogre::Entity *e;
  if (mSceneMgr->hasEntity(ss.str()))
    {
      this->moveEntity(entityId, x, y, angle);
      return (true);
      e = mSceneMgr->createEntity(ss.str(), name);
    }
  catch (Ogre::Exception &e)
    {
      return false;
    }
  Ogre::SceneNode *s = worldNode->createChildSceneNode("PLayerNode");
  this->rootNode = s;
  s->setPosition(x, y, 0);
  s->yaw(Ogre::Radian(world::Math::toRad(degres)));
  rootNode->attachObject(e);
  rootNode->attachObject(mCamera);
  mCamera->pitch(Ogre::Degree(-89));
  mCamera->yaw(Ogre::Degree(20));
  return (true);
}

__attribute_deprecated__ __attribute_warn_unused_result__ bool OgreUI::addWorldEntity(
	int entityId, const std::string &name, int x, int y,
	short degres, int texture_id)
{
  std::stringstream ss;
  ss << entityId;
  Ogre::Entity *e;
  try
    {
      e = mSceneMgr->createEntity(ss.str(), meshmap.at(meshid).c_str());
    }
  catch (Ogre::Exception &e)
    {
      return false;
    }
  if (texture_id != Texturename::TEXTURE_NONE)
    e->setMaterialName(texturemap[texture_id]);
  Ogre::SceneNode *s = worldNode->createChildSceneNode(ss.str());
  s->setPosition(x, y, 0);
  s->yaw(Ogre::Radian(world::Math::toRad(angle)));
  s->attachObject(e);
  return (true);
}

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
							     const std::string &name,
							     std::pair<int, int> position,
							     Ogre::Vector3 orientation,
							     int textureId)
{
  std::stringstream ss;
  ss << entityId;
  Ogre::Entity *e;
  try
    {
      e = mSceneMgr->createEntity(ss.str(), name);
    }
  catch (Ogre::Exception &e)
    {
      return false;
    }
  Ogre::SceneNode *s = worldNode->createChildSceneNode(ss.str());
  s->setPosition(position.first, position.second, 0);
  s->pitch(
	  Ogre::Radian(world::Math::toRad(static_cast<short >(orientation.x))));
  s->yaw(Ogre::Radian(world::Math::toRad(static_cast<short >(orientation.y))));
  s->roll(Ogre::Radian(world::Math::toRad(static_cast<short >(orientation.z))));
  s->attachObject(e);
  return (true);
}

#warning "C'est la faute à trouvé"

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
							     const std::string &name,
							     std::pair<int, int> position)
{
  return this->addWorldEntity(entityId, name, position, Ogre::Vector3(0, 0, 0),
			      -1);
}

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
							     const std::string &name,
							     std::pair<int, int> position,
							     int textureId)
{
  return this->addWorldEntity(entityId, name, position, Ogre::Vector3(0, 0, 0),
			      textureId);
}

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
							     const std::string &name,
							     std::pair<int, int> position,
							     Ogre::Vector3 orientation)
{
  return this->addWorldEntity(entityId, name, position, orientation, -1);
}

void OgreUI::setQuality(int percent)
{
  this->quality = percent;
}

int OgreUI::triggerEffect(int id, gauntlet::EffectType type,
			  std::pair<double, double> coord)
{
  std::stringstream ss;

  ss << "effect" << id;
  Effect *&mapped_type = this->effectMap[id];
  if (mapped_type != NULL)
    {
//      delete (mapped_type);
    }
  gauntlet::Effect *effect = new gauntlet::Effect(this, type, ss.str(), coord,
						  this->quality);
  mapped_type = effect;
  return 0;
}

void OgreUI::removeEntity(int id)
{
  std::stringstream ss;
  ss << id;
  mSceneMgr->destroyEntity(ss.str());
  mSceneMgr->destroySceneNode(ss.str());
}

void OgreUI::stopEffect(int id)
{
  Ogre::ParticleSystem *pSystem = this->effectMap[id]->getParticleSystem();

  pSystem->setEmitting(false);
}

void OgreUI::moveEntity(int id, int x, int y, short degres)
{
  std::stringstream ss;
  ss << id;

  Ogre::SceneNode *s = mSceneMgr->getSceneNode(ss.str());
  s->setPosition(x, y, 0);
  s->yaw(Ogre::Radian(world::Math::toRad(degres)));
}

void OgreUI::addCameraTracker(int id)
{
  std::stringstream ss;
  ss << id;
  Ogre::SceneNode *s = mSceneMgr->getSceneNode(ss.str());
  s->attachObject(mCamera);
  mCamera->pitch(Ogre::Degree(-89));
  mCamera->yaw(Ogre::Degree(20));
}

bool OgreUI::frameStarted(const Ogre::FrameEvent &evt)
{
  if (obs != NULL)
    obs->frameStarted();
  return true;
}

bool OgreUI::addMapEntity(int entityId, gauntlet::EntityName meshid, int x,
			  int y, short angle, gauntlet::Texturename texture_id)
{
  std::stringstream ss;
  ss << entityId;
  Ogre::Entity *e;
  if (mSceneMgr->hasEntity(ss.str()) == true)
    {
      this->moveEntity(entityId, x, y, angle);
      return (true);
    }
  try
    {
      e = mSceneMgr->createEntity(ss.str(), meshmap.at(meshid).c_str());
    }
  catch (Ogre::Exception &e)
    {
      return false;
    }
  if (texture_id != Texturename::TEXTURE_NONE)
    e->setMaterialName(texturemap.at(texture_id));
  Ogre::SceneNode *s = planNode->createChildSceneNode(ss.str());
  s->setPosition(x, y, 0);
  s->setScale(0.5, 0.5, 0.5);
  s->yaw(Ogre::Radian(world::Math::toRad(angle)));
  s->attachObject(e);
  return (true);
}

void OgreUI::resetMap()
{
  if (planNode)
    {
      planNode->removeAndDestroyAllChildren();
    }
}

