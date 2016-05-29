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
#include <gameData/EntityName.hh>
#include <gameData/TextureName.hh>
#include <gameData/SoundName.hh>
#include "IUIObserver.hh"
#include "AnimationsList.hh"

namespace gauntlet
{
  enum EffectName : int;

  class Effect;

  namespace animations
  {
	class Animation;
    	class JSON;
  }
}

class OgreUI
	: public Ogre::FrameListener,
	  public Ogre::WindowEventListener,
	  public OIS::KeyListener,
	  public OIS::MouseListener,
	  OgreBites::SdkTrayListener
{
 private:
  static const std::map<OIS::KeyCode, gauntlet::core::IUIObserver::Key> keymap;
  static const std::map<OIS::MouseButtonID, gauntlet::core::IUIObserver::Key> mousemap;
  static const std::map<gauntlet::core::Position, OgreBites::TrayLocation> posmap;
  static const std::map<gauntlet::TextureName, std::string> texturemap;
  static const std::map<gauntlet::EntityName, std::string> meshmap;
  static const std::map<gauntlet::SoundName, std::string> soundmap;
  Ogre::LightList lightList;

  std::map<std::string, Ogre::AnimationState *> animationsArray;
  std::map<std::string, gauntlet::animations::Animation *> animationsMap;
  std::map<int, gauntlet::Effect *> effectMap;

  gauntlet::core::IUIObserver *obs;
  OgreOggSound::OgreOggSoundManager *mSoundManager;


  Ogre::Root *mRoot;
  Ogre::Camera *mCamera;
  Ogre::SceneManager *mSceneMgr;
  Ogre::RenderWindow *mWindow;

  Ogre::String mResourcesCfg;
  Ogre::String mPluginsCfg;

  Ogre::SceneNode *planNode;
  Ogre::SceneNode *worldNode;

  Ogre::SceneNode *rootNode;
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


  bool addWorldEntity(int entityId, gauntlet::EntityName meshid, int x, int y,
		      short degres, gauntlet::TextureName texture_id);

  bool addMapEntity(int entityId, gauntlet::EntityName meshid, int x, int y,
		    short degres, gauntlet::TextureName texture_id);

  void initSound();

  bool configure(void);

  void resetMap();

  void chooseSceneManager(void);

  void createCamera(void);

  void createFrameListener(void);

  void addCameraTracker(int id);

  bool frameStarted(const Ogre::FrameEvent &evt);

  void createScene(void);

  void removeEntity(int id);

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

  void removeItem(int ID);

  void sliderMoved(OgreBites::Slider *slider);

  void setIObserver(gauntlet::core::IUIObserver *Obs);

  bool loadSound(int id, gauntlet::SoundName name);

  void load3dSound(int id, gauntlet::SoundName name, int x, int y);

  void hideItem(int id);

  bool playSound(int id, gauntlet::SoundName name, bool loop);

  void stopSound(int id);

  void showItem(int id);

  void playAnimation(int entityId, int animationId, bool loop);

  void playAnimation(int entityId,
		     gauntlet::animations::AnimationsListJson animationId,
		     bool loop);

  void showBackground();

  void hideBackground();

  void stopAnimation(int animationId, int entityId);


  std::pair<int, int> getSizeWindow();

  void setQuality(int percent = 100);

  int getQuality() const;

  void quit();

  Ogre::SceneManager *getSceneManager();

  int triggerEffect(int id, gauntlet::EffectName ef,
		    std::pair<double, double> pair);

  int triggerEffect(int id, gauntlet::EffectName ef,
		    std::pair<double, double> pair,
		    std::tuple<double, double, double> orientation);

  int triggerEffect(int id, gauntlet::EffectName type,
		    std::pair<double, double> coord, double yRotation);

  void moveEntity(int id, int x, int y, short degres);

  void stopEffect(int id);

  bool addWorldEntity(int entityId, const std::string &name,
		      std::pair<int, int>);


  bool addWorldEntity(int entityId, const std::string &name,
		      std::pair<int, int>,
		      Ogre::Vector3 orientation);

  void playAnimation(int entityId, const std::string &animationName, bool loop);


  bool addWorldEntity(int entityId, const std::string &name,
		      std::pair<int, int> position, Ogre::Vector3 orientation,
		      gauntlet::TextureName textureId);

  bool addWorldEntity(int entityId, const std::string &name,
		      std::pair<int, int> position,
		      gauntlet::TextureName textureId);

  bool entityExist(int id);

 private:

  void applyAnimation(const Ogre::FrameEvent &evt);

  void createLight(unsigned int height, unsigned int width,
		   unsigned int interval);

  const std::string &getAnimationName(int animationId,
				      const Ogre::Entity *pEntity) const;
};
