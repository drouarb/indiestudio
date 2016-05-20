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

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <core/Position.hh>
#include "IUIObserver.hh"

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
    virtual void createScene(void);
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual void buttonHit(OgreBites::Button* button);
    virtual void itemSelected(OgreBites::SelectMenu* menu);
    virtual void checkBoxToggled(OgreBites::CheckBox *checkBox);
    void updateItemValue(int itemid, struct gauntlet::core::t_hitItem item);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
     virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
	void addButton(gauntlet::core::Position  pos, int id, std::string text, int texture_id);
	void addSlideBar(gauntlet::core::Position  pos, int id, std::string text, int max_value, int texture_id);
    void addCheckbox(gauntlet::core::Position  pos, int id, std::string text, int texture_id);
    void addTextbox(gauntlet::core::Position  pos, int id, std::string text, int texture_id);
    void addSelectMenu(gauntlet::core::Position pos, int id, std::string name, std::vector<std::string>,
                               int texture_id);
    void addProgressBar(gauntlet::core::Position pos, int id, std::string text, int texture_id, int value);
    void remove(int ID);
    virtual void sliderMoved(OgreBites::Slider* slider);
    virtual void setIObserver(gauntlet::core::IUIObserver * Obs);
    void loadSound(std::string & path);
     void hideItem(int id);
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