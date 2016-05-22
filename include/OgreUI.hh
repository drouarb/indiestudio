#pragma once


#ifdef OGRE_STATIC
#include <OgreGLPlugin.h>
  #include <OgreParticleFXPlugin.h>
  #include <OgreBspSceneManagerPlugin.h>
  #include <OgrePCZPlugin.h>
  #include <OgreOctreePlugin.h>
  #include <OgreOctreeZonePlugin.h>
  #include <OgreOggSoundPlugin.h>
#endif

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
#include <mutex>
#include <graph/Effect.hh>
#include "IUIObserver.hh"

namespace gauntlet
{
  enum EffectType : int;
  class Effect;
}

class OgreUI
	: public Ogre::FrameListener,
	  public Ogre::WindowEventListener,
	  public OIS::KeyListener,
	  public OIS::MouseListener,
	  OgreBites::SdkTrayListener
{
 private:
  std::map<OIS::KeyCode, gauntlet::core::IUIObserver::Key> keymap;
  std::map<OIS::MouseButtonID, gauntlet::core::IUIObserver::Key> mousemap;
  std::map<gauntlet::core::Position, OgreBites::TrayLocation> posmap;
  std::map<std::string, Ogre::AnimationState *> animationsArray;
  std::map<int, gauntlet::Effect *> effectMap;
  gauntlet::core::IUIObserver *obs;
  OgreOggSound::OgreOggSoundManager *mSoundManager;


  Ogre::Root *mRoot;
  Ogre::Camera *mCamera;
  Ogre::SceneManager *mSceneMgr;
  Ogre::RenderWindow *mWindow;
  Ogre::String mResourcesCfg;
  Ogre::String mPluginsCfg;
 private:
  Ogre::SceneNode *rootNode;
  Ogre::SceneNode *worldNode;
  Ogre::OverlaySystem *mOverlaySystem;
  OgreBites::SdkTrayManager *mTrayMgr;
  OgreBites::SdkCameraMan *mCameraMan;
  OgreBites::ParamsPanel *mDetailsPanel;
  bool mCursorWasVisible;
  bool mShutDown;
  OIS::InputManager *mInputManager;
  OIS::Mouse *mMouse;
  OIS::Keyboard *mKeyboard;
  int quality = 100;

 public:
  bool init();

  void go();

  bool setup();


  void addWorldEntity(int entityId, std::string &name, int x, int y,
			short degres, int texture_id);
  void addRootEntity(int entityId, std::string &name, int x, int y,
		       int degres);

  void initMap();

  void initSound();

  bool configure(void);

  void chooseSceneManager(void);

  void createCamera(void);

  void createFrameListener(void);

  void createScene(void);

  OgreUI(void);

  ~OgreUI(void);

  void destroyScene(void);

  void createViewports(void);

  void setupResources(void);

  void createResourceListener(void);

  void loadResources(void);

  void buttonHit(OgreBites::Button *button);

  void itemSelected(OgreBites::SelectMenu *menu);

  void checkBoxToggled(OgreBites::CheckBox *checkBox);

  void updateItemValue(int itemid, struct gauntlet::core::t_hitItem item);

  bool frameRenderingQueued(const Ogre::FrameEvent &evt);

  bool keyPressed(const OIS::KeyEvent &arg);

  bool keyReleased(const OIS::KeyEvent &arg);

  bool mouseMoved(const OIS::MouseEvent &arg);

  bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

  bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

  void windowResized(Ogre::RenderWindow *rw);

  void windowClosed(Ogre::RenderWindow *rw);

  void addButton(gauntlet::core::Position pos, int id, std::string text,
		 int texture_id);

  void addSlideBar(gauntlet::core::Position pos, int id, std::string text,
		   int max_value, int texture_id);

  void addCheckbox(gauntlet::core::Position pos, int id, std::string text,
		   int texture_id);

  void addTextbox(gauntlet::core::Position pos, int id, std::string text,
		  int texture_id);

  void addLabel(gauntlet::core::Position pos, int id, std::string text,
		int texture_id);

  void addSelectMenu(gauntlet::core::Position pos, int id, std::string name,
		     std::vector<std::string> &,
		     int texture_id);

  void addProgressBar(gauntlet::core::Position pos, int id, std::string text,
		      int texture_id, int value);

  void remove(int ID);

  void sliderMoved(OgreBites::Slider *slider);

  void setIObserver(gauntlet::core::IUIObserver *Obs);

  void loadSound(int id, std::string &path);

  void hideItem(int id);

  void playSound(int id);

  void stopSound(int id);

  void showItem(int id);

  void playAnimation(int animationId, int entityId, bool loop);

  void showBackground();

  void hideBackground();

  void stopAnimation(int animationId, int entityId);

  std::pair<int, int> getSizeWindow();

  void setQuality(int percent = 100);

  void quit();

  Ogre::SceneManager *getSceneManager();

  int triggerEffect(int id, gauntlet::EffectType ef, std::pair<double, double> pair);

};
