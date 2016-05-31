#include <OIS/OIS.h>
#include <iostream>
#include "graph/OgreUI.hh"
#include "Math.hh"
#include "Animations.hh"

using namespace gauntlet;
using namespace core;

namespace gauntlet
{
    enum EffectName : int;

    class Effect;

    namespace animations
    {
        class Animation;

        class JSONAnimation;
    }
}


OgreUI::OgreUI(void)
        : obs(NULL),

          mRoot(0),
          mCamera(0),
          mSceneMgr(0),
          mWindow(0),

          mResourcesCfg(Ogre::StringUtil::BLANK),
          mPluginsCfg(Ogre::StringUtil::BLANK),

          planNode(0),

          mTrayMgr(0),
          mCameraMan(0),
          mDetailsPanel(0),

          mCursorWasVisible(true),
          mShutDown(false),

          mInputManager(0),
          mMouse(0),
          mKeyboard(0)
{
    rootNode = NULL;
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
    mSceneMgr->createSceneNode()->attachObject(mCamera);
    mCamera->setPosition(Ogre::Vector3(0, 100, 80));
    mCamera->setNearClipDistance(5);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void OgreUI::createFrameListener(void)
{
    // Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
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
    applyAnimation(evt);
    mSoundManager->update(evt.timeSinceLastFrame);
    if (!mTrayMgr->isDialogVisible())
        {
            mCameraMan->frameRenderingQueued(evt);
        }

    return true;
}

void OgreUI::applyAnimation(const Ogre::FrameEvent &evt)
{
//  for (auto animation : animationsArray)
//    {
//      Ogre::AnimationState *t2 = animation.second;
//      t2->addTime(evt.timeSinceLastFrame);
//    }
    for (auto animation : this->animationsMap)
        {
            animations::Animation *t2 = animation.second;
            if (!t2)
                continue;
//      std::cout << "AAA Animation: " << animation.first << ", " <<
//      animation.second->getName() << std::endl;

            if (!t2->update(evt.timeSinceLastFrame))
                {
                    this->animationsMap[animation.first] = NULL;
                }

        }
}

bool OgreUI::keyPressed(const OIS::KeyEvent &arg)
{
    //mCameraMan->injectKeyDown(arg);
    if (obs != NULL) if (keymap.count(arg.key) > 0)
        {
            obs->keyDown(keymap.at(arg.key));
        }
    return true;
}

bool OgreUI::keyReleased(const OIS::KeyEvent &arg)
{
//  mCameraMan->injectKeyUp(arg);
    if (obs != NULL) if (keymap.count(arg.key) > 0)
        obs->keyUp(keymap.at(arg.key));
    return true;
}

bool OgreUI::mouseMoved(const OIS::MouseEvent &arg)
{
    //mCameraMan->injectMouseMove(arg);
    mTrayMgr->injectMouseMove(arg);
    if (obs != NULL)
        obs->mouseMove(arg.state.X.abs, arg.state.Y.abs);
    return true;
}

bool OgreUI::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    mTrayMgr->injectMouseDown(arg, id);
    if (obs != NULL) if (mousemap.count(id) > 0)
        obs->keyDown(mousemap.at(id));
    return true;
}

bool OgreUI::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    mTrayMgr->injectMouseUp(arg, id);
    if (obs != NULL) if (mousemap.count(id) > 0)
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

bool OgreUI::loadSound(int id, SoundName name)
{
    std::stringstream ss;
    ss << id;

    if (name != SOUND_NONE)
        {
            if (access(("../media/sounds/" + soundmap.at(name)).c_str(), F_OK) == 0)
                {
                    mSoundManager->createSound(ss.str() + "_sound", soundmap.at(name), true, false,
                                               false);
                    return (true);
                }
            else
                return (false);
        }
    return true;
}

bool OgreUI::playSound(int id, gauntlet::SoundName name, bool loop)
{
    std::stringstream ss;
    ss << id;

    if (name == SOUND_NONE)
        {
            return (true);
        }
    try
        {
            if (!mSoundManager->hasSound(ss.str() + "_sound")) if (loadSound(id, name) == false)
                {
                    std::cerr << "sound " << name << "doesn t exit" << std::endl;
                    return false;
                }
            if (mSoundManager->hasSound(ss.str() + "_sound"))
                {

                    mSoundManager->getSound(ss.str() + "_sound")->play();
                    mSoundManager->getSound(ss.str() + "_sound")->loop(loop);
                    return (true);
                }
        }
    catch (std::exception &e)
        {
            std::cerr << " ca a pété sur " << soundmap.at(name) << std::endl;
//      std::cerr << e.what() << std::endl;
        }
    return (false);
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
    OgreBites::ProgressBar *p = mTrayMgr->createProgressBar(posmap.at(pos),
                                                            ss.str(),
                                                            text, 300, 10);
    p->setProgress((float) value / 100);
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
    mTrayMgr->createLongSlider(posmap.at(pos), ss.str(), text, 100, 100, 1, max,
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
                    OgreBites::Slider *s = static_cast<OgreBites::Slider *>
                    (mTrayMgr->getWidget(ss.str()));
                    s->setValue(item.value, true);
                }
            break;
            case MenuItemType::PROGRESSBAR:
                {
                    OgreBites::ProgressBar *p = static_cast<OgreBites::ProgressBar *>
                    (mTrayMgr->getWidget(
                                    ss.str()));
                    p->setProgress((float) item.value / 100);
                }
            break;
            case MenuItemType::TEXTBOX:
                {
                    OgreBites::TextBox *t = static_cast<OgreBites::TextBox *>(mTrayMgr->getWidget
                            (ss.str()));
                    t->setText(item.data);
                }
            break;
            case MenuItemType::LABEL:
                {
                    OgreBites::Label *label = static_cast<OgreBites::Label *>(mTrayMgr->getWidget
                            (ss.str()));
                    label->setCaption(item.data);
                }
            break;
            case MenuItemType::CHECKBOX:
                {
                    OgreBites::CheckBox *c = static_cast<OgreBites::CheckBox *>(mTrayMgr->getWidget
                            (ss.str()));
                    if (item.state == CHECKED)
                        c->setChecked(true, true);
                    else
                        c->setChecked(false, true);
                }
            default:
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
    mTrayMgr->createLabel(posmap.at(pos), ss.str(), text, text.size() * 11 + 20);
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
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT, true);
    mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox");
    createAmbientLight();
}

void OgreUI::createAmbientLight()
{
    Ogre::Light *pointLight = mSceneMgr->createLight("PointLight");
    pointLight->setSpotlightInnerAngle(Ogre::Radian(0));
    mSceneMgr->setAmbientLight(Ogre::ColourValue::White);
    pointLight->setSpotlightOuterAngle((Ogre::Degree(180)));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
    this->createLight(200, 200, 50);
    pointLight->setPowerScale(8900000);
    Ogre::Light *pointLight2 = mSceneMgr->createLight("PointLight2");
    pointLight2->setPosition(0, 200, 200);
    pointLight2->setPowerScale(8900000);
    Ogre::Light *pointLight3 = mSceneMgr->createLight("PointLight3");
    pointLight3->setPosition(0, 200, -200);
    pointLight3->setPowerScale(8900000);
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
    Ogre::AnimationStateSet *allAnims;

    if ((allAnims = pEntity->getAllAnimationStates()) == NULL)
        return;
    Ogre::AnimationStateIterator mapIterator = allAnims->getAnimationStateIterator();
    auto it = mapIterator.begin();
    while (it != mapIterator.end())
        {
            if (nb == animationId)
                {
                    this->playAnimation(entityId, (*it).first, loop);
                    return;
                }
            it++;
            ++nb;
        }
}


void OgreUI::playAnimation(int entityId,
                           gauntlet::animations::AnimationsListJson animation,
                           bool loop)
{
    std::pair<std::string, std::string> pair;
    try {
        pair = animations::jsonMap.at(
                        animation);
    } catch (...)
    {
        std::cerr << "Not found : " << animation << std::endl;
    }
  Ogre::Entity *pEntity;
  Ogre::AnimationState *pState;
  std::stringstream ss;

    try
        {
            ss << entityId;
            pEntity = this->mSceneMgr->getEntity(ss.str());
            if (pEntity == NULL)
                {
                    std::cerr << "Entité pas trouvée : " << ss.str() << std::endl;
                    return;
                }
            pState = pEntity->getAnimationState(
                    getAnimationName(0, pEntity));
        } catch (std::exception &e)
        {
            return;
        }
    pState->setLoop(loop);
    pState->setEnabled(true);
    animations::Animation *a = NULL;
    try
        {
            a = new animations::JSONAnimation(pair.first,
                                              pair.second,
                                              pState, loop);
        } catch (std::logic_error &e)
        {
            std::cerr << "not found :" << e.what() << std::endl;
        } catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    animations::Animation **type = &this->animationsMap[pEntity->getName()];
    if (*type)
        {
            (*type)->reset();
            delete (*type);
        }
    (*type) = a;
    a->update(0);
}

const std::string &OgreUI::getAnimationName(int animationId,
                                            const Ogre::Entity *pEntity) const
{
    int nb = 0;
    Ogre::AnimationStateSet *allAnims;
    if ((allAnims = pEntity->getAllAnimationStates()) == NULL)
        throw std::logic_error("Unknow Animation id");
    Ogre::AnimationStateIterator mapIterator = allAnims->getAnimationStateIterator();
    auto it = mapIterator.begin();
    while (it != mapIterator.end())
        {
            if (nb == animationId)
                {
                    return it->first;
                }
            it++;
            ++nb;
        }
    throw std::logic_error("Unknow Animation id");
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
    mTrayMgr->showBackdrop("Ogre/BackgroundHell");
}

void OgreUI::hideBackground()
{
    mTrayMgr->hideBackdrop();
}

void OgreUI::initSound()
{
    this->mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    mSoundManager->init("Gauntlet");
}

void OgreUI::stopSound(int id)
{
    std::stringstream ss;
    ss << id;
    mSoundManager->getSound(ss.str() + "_sound")->stop();
}

Ogre::SceneManager *OgreUI::getSceneManager()
{
    return this->mSceneMgr;
}


bool __attribute_deprecated__ OgreUI::addWorldEntity(int entityId,
                                                     EntityName meshid, int x,
                                                     int y,
                                                     short angle,
                                                     TextureName texture_id)
{
    std::stringstream ss;
    ss << entityId;
    Ogre::Entity *e;
    int z = 0;
    if (mSceneMgr->hasEntity(ss.str()))
        {
            this->moveEntity(entityId, x, y, angle);
            return (true);
        }
    try
        {
            e = mSceneMgr->createEntity(ss.str(), meshmap.at(meshid).c_str());
        } catch (Ogre::Exception &e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
    if (texture_id != TextureName::TEXTURE_NONE)
        e->setMaterialName(texturemap.at(texture_id));
    Ogre::SceneNode *s = worldNode->createChildSceneNode(ss.str());
    if (this->heightmap.isLoaded())
        z = this->heightmap.at(x, y);
    s->setPosition(x, z, y);
    scaleEntity(s, meshid);
    s->attachObject(e);
    return (true);
}

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
                                                             const std::string &name,
                                                             std::pair<int, int> position,
                                                             Ogre::Vector3 orientation,
                                                             TextureName textureId)
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


bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
                                                             const std::string &name,
                                                             std::pair<int, int> position)
{
    return this->addWorldEntity(entityId, name, position, Ogre::Vector3(0, 0, 0),
                                TextureName::TEXTURE_NONE);
}

bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
                                                             const std::string &name,
                                                             std::pair<int, int> position,
                                                             TextureName textureId)
{
    return this->addWorldEntity(entityId, name, position, Ogre::Vector3(0, 0, 0),
                                textureId);
}


bool __attribute_warn_unused_result__ OgreUI::addWorldEntity(int entityId,
                                                             const std::string &name,
                                                             std::pair<int, int> position,
                                                             Ogre::Vector3 orientation)
{
    return this->addWorldEntity(entityId, name, position, orientation,
                                TextureName::TEXTURE_NONE);
}


void OgreUI::setQuality(int percent)
{
    this->quality = percent;
}

int OgreUI::getQuality() const
{
    return this->quality;
}

int OgreUI::triggerEffect(int id, gauntlet::EffectName type,
                          std::pair<double, double> coord)
{
    std::stringstream ss;

    ss << "effect" << id;
    Effect *&mapped_type = this->effectMap[id];
    gauntlet::Effect *effect = new gauntlet::Effect(this, type, ss.str(), coord,
                                                    this->quality);
    mapped_type = effect;
    return 0;
}

int OgreUI::triggerEffect(int id, gauntlet::EffectName type,
                          std::pair<double, double> coord,
                          std::tuple<double, double, double> orientation)
{
    std::stringstream ss;

    ss << "effect" << id;
    Effect *&mapped_type = this->effectMap[id];
    gauntlet::Effect *effect = new gauntlet::Effect(this, type, ss.str(), coord,
                                                    this->quality);
    mapped_type = effect;
    effect->getParticleSystem()->getEmitter(0)->setDirection(
            Ogre::Vector3(std::get<0>(orientation), std::get<1>(orientation),
                          std::get<2>(orientation)));
    return 0;
}

int OgreUI::triggerEffect(int id, gauntlet::EffectName type,
                          std::pair<double, double> coord,
                          double yRotation)
{
    std::stringstream ss;

    ss << "effect" << id;
    Effect *&mapped_type = this->effectMap[id];
    gauntlet::Effect *effect = new gauntlet::Effect(this, type, ss.str(), coord,
                                                    this->quality);
    mapped_type = effect;
    effect->getParticleSystem()->getEmitter(0)->setDirection(
            Ogre::Vector3(0, yRotation, 0));
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
    int z = 0;
    int diff = 0;
    std::stringstream ss;
    ss << id;
    if (this->heightmap.isLoaded())
        {
            z = this->heightmap.at(x, y);
        }
    Ogre::SceneNode *s = mSceneMgr->getSceneNode(ss.str());
    Ogre::Vector3 des(x, z, y);
    if (des != s->getPosition())
        diff = 1;
    Ogre::Vector3 direction;
    direction = des - s->getPosition();
    direction.normalise();
    s->setPosition(x, z, y);
    if (rootNode != NULL && s == rootNode)
        {
            if (diff == 1)
                {
                    mCamera->setPosition(s->getPosition().x, mCamera->getPosition().y,
                                         s->getPosition().z - 500);
                }
        }
    s->yaw(Ogre::Radian(world::Math::toRad(degres)) -
           s->getOrientation().getYaw());
}

void OgreUI::addCameraTracker(int id)
{
    std::stringstream ss;
    ss << id;
    Ogre::SceneNode *s = mSceneMgr->getSceneNode(ss.str());
    rootNode = s;
    mCamera->setPosition(s->getPosition().x, s->getPosition().y + 800,
                         s->getPosition().z - 500);
    mCamera->lookAt(s->getPosition());
}

bool OgreUI::frameStarted(const Ogre::FrameEvent &evt)
{
    if (obs != NULL)
        obs->frameStarted();
    return true;
}

bool OgreUI::addMapEntity(int entityId, gauntlet::EntityName meshid, int x,
                          int y, short angle, gauntlet::TextureName texture_id)
{
    std::stringstream ss;
    ss << entityId;
    int z = 0;
    Ogre::Entity *e;
    if (this->heightmap.isLoaded())
        {
            z = this->heightmap.at(x, y);
        }
    try
        {
            e = mSceneMgr->createEntity(ss.str(), meshmap.at(meshid).c_str());
        }
    catch (Ogre::Exception &e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
    if (texture_id != TextureName::TEXTURE_NONE)
        e->setMaterialName(texturemap.at(texture_id));
    Ogre::SceneNode *s = planNode->createChildSceneNode(ss.str());
    s->setPosition(x, z, y);
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

bool OgreUI::entityExist(int id)
{
    std::stringstream ss;
    ss << id;
    if (mSceneMgr->hasEntity(ss.str()) == true)
        return (true);
    return false;
}

void OgreUI::createLight(unsigned int height, unsigned int width,
                         unsigned int interval)
{
    for (int x = -width, y = -height; x < (int) width && y <
                                                         (int) height; x += (int) interval, y += (int) interval)
        {
            Ogre::Light *pLight = this->mSceneMgr->createLight();

            pLight->setType(Ogre::Light::LT_POINT);
            pLight->setPowerScale(100000);
            pLight->setPosition(x, 0, y);
            this->lightList.push_back(pLight);
        }
}

void OgreUI::play3dSound(int id, SoundName name, int x, int y, bool loop)
{

    std::stringstream ss;
    ss << id;
    OgreOggSound::OgreOggISound *sound = 0;
    int z = 0;

    if (this->heightmap.isLoaded())
        {
            z = this->heightmap.at(x, y);
        }
    if (name != SOUND_NONE) if ((sound = mSoundManager->createSound(ss.str() + "_sound", soundmap.at(name))))
        {
            sound->loop(loop);
            sound->setVolume(0);
            std::cerr << id << std::endl;
            Ogre::SceneNode *node = planNode->createChildSceneNode(ss.str() + "_sound");
            node->setPosition(x, z, y);
            if (rootNode != NULL)
                {
                    calcNewVolume(id, rootNode->getPosition(), node->getPosition());
                }
            else
                {
                    sound->setVolume(1);
                    sound->play();
                }
        }
}

bool OgreUI::loadMap(const std::string &map)
{
    return (this->heightmap.load(map));
}

bool OgreUI::addMapEntity(int entityId, const std::string &path, int x, int y,
                          short angle, gauntlet::TextureName texture_id)
{
    std::stringstream ss;
    ss << entityId;
    int z = 0;
    Ogre::Entity *e;
    try
        {
            e = mSceneMgr->createEntity(ss.str(), path);
        }
    catch (Ogre::Exception &e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
    if (texture_id != TextureName::TEXTURE_NONE)
        e->setMaterialName(texturemap.at(texture_id));
    Ogre::SceneNode *s = planNode->createChildSceneNode(ss.str());
    std::pair<double, double> size = {0, 0};
    if (heightmap.isLoaded())
        {
            size = heightmap.getSize();
        }
    s->scale(SCALE_MAP, SCALE_MAP, SCALE_MAP);
    s->yaw(Ogre::Radian(world::Math::toRad(angle)));
    s->attachObject(e);
    return (true);
}

void OgreUI::scaleEntity(Ogre::SceneNode *s, gauntlet::EntityName id)
{
    switch (id)
        {
            case EntityName::SKELETON_WARLORD:
                s->scale(0.4, 0.4, 0.4);
            break;
            case EntityName::SKELETON_FOOTMAN:
                s->scale(0.4, 0.4, 0.4);
            break;
            case EntityName::SKELETON_ARCHER:
                s->scale(0.4, 0.4, 0.4);
            break;
            case EntityName::SKELETON_SORCERER:
                s->scale(0.4, 0.4, 0.4);
            break;
            case EntityName::CHEST:
                s->scale(100, 100, 100);
            break;
            default:
                break;
        }
}

void OgreUI::muetAllSound()
{
    mSoundManager->muteAllSounds();
}

void OgreUI::pauseSound(int id)
{
    std::stringstream ss;
    ss << id;
    mSoundManager->getSound(ss.str())->pause();
}

void OgreUI::showBackground(gauntlet::BackgroundName background)
{
    try
        {
            mTrayMgr->showBackdrop(backgroundmap.at(background));
        }
    catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
}

void OgreUI::showCharacterSelectMenu(CharacterMenuName name)
{
    if (mTrayMgr->getWidget("MenuCharacterSelection"))
        {
            mTrayMgr->destroyWidget("MenuCharacterSelection");
            mTrayMgr->createDecorWidget(OgreBites::TL_RIGHT, "MenuCharacterSelection",
                                        charactermap.at(name));
        }
    else
        mTrayMgr->createDecorWidget(OgreBites::TL_RIGHT, "MenuCharacterSelection",
                                    charactermap.at(name));
}

void OgreUI::hideCharacterSelectMenu()
{
    if (mTrayMgr->getWidget("MenuCharacterSelection"))
        {
            mTrayMgr->destroyWidget("MenuCharacterSelection");
        }
}

void OgreUI::increaseVolume(int id, float value)
{
    std::stringstream ss;
    ss << id;
    OgreOggSound::OgreOggISound *s = mSoundManager->getSound(ss.str());
    if (s->getVolume() + value < 100)
        {
            s->setVolume(s->getVolume() + value);
        }
}

void OgreUI::decreaseVolume(int id, float value)
{
    std::stringstream ss;
    ss << id;
    if (mSoundManager->hasSound(ss.str()))
        {
            OgreOggSound::OgreOggISound *s = mSoundManager->getSound(ss.str());
            if (s->getVolume() - value >= 0)
                {
                    s->setVolume(s->getVolume() - value);
                }
        }
}

void OgreUI::calcNewVolume(int id, Ogre::Vector3 player, Ogre::Vector3 obj)
{
    std::stringstream ss;
    ss << id;
    float res;

    if (mSoundManager->hasSound(ss.str() + "_sound"))
        {
            OgreOggSound::OgreOggISound *s = mSoundManager->getSound(
                    ss.str() + "_sound");
            if ((res = std::sqrt(pow((obj.x - player.x), 2) + (player.z - obj.z))) <
                MAX_DISTANCE)
                {
                    s->setVolume((MAX_DISTANCE - res) * 1 / MAX_DISTANCE);
                    if (!s->isPlaying())
                        s->play();
                }
            else
                s->setVolume(0);
        }
}


















