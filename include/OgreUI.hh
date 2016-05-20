#ifndef Ogreui_h
#define Ogreui_h

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "IUIObserver.hh"
#include "Position.hh"

class  OgreUI : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
    OgreUI(void);
    virtual ~OgreUI(void);
    std::map<OIS::KeyCode , gauntlet::core::IUIObserver::Key> keymap;
    std::map<OIS::MouseButtonID , gauntlet::core::IUIObserver::Key> mousemap;
	std::map<gauntlet::core::Position, OgreBites::TrayLocation> posmap;
    virtual void go(void);
    gauntlet::core::IUIObserver *obs;
protected:
    virtual bool setup();
    virtual void initMap();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0;
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual void buttonHit(OgreBites::Button* button);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
     virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
    virtual void addButton(gauntlet::core::Position  pos, int id, std::string text, int texture_id);
    void remove(int ID);
    virtual void setIObserver(gauntlet::core::IUIObserver * Obs);
    void loadSound(std::string & path);
    void playSound(int id);
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
	Ogre::OverlaySystem *mOverlaySystem;
    OgreBites::SdkTrayManager* mTrayMgr;
    OgreBites::SdkCameraMan* mCameraMan;
    OgreBites::ParamsPanel* mDetailsPanel;
    bool mCursorWasVisible;
    bool mShutDown;
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
};

#endif