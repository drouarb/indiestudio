#include "TutorialApplication.h"
#include "OgreUI.h"


//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{

    mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));

    Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(250, 150, 250);
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);

//    Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("tudorhouse.mesh");
//    Ogre::SceneNode* ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
//    ninjaEntity->setMaterialName("Examples/TudorHouses");
//    ninjaNode->attachObject(ninjaEntity);
//    std::string kkk = "kokok";
//    addButton(gauntlet::core::PTOPLEFT, 567 , kkk, 0);

//    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
//    CEGUI::Font::setDefaultResourceGroup("Fonts");
//    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
//    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
//    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
//
//
//    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
//    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
//    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
//    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
//    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Ogre");
    ogreNode->attachObject(ogreEntity);
//    Ogre::Light* light = mSceneMgr->createLight("MainLight");
//    light->setPosition(2000, 0, 50);
//    ogreNode->attachObject(light);
//    Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
//
//    Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(
//            Ogre::Vector3(84, 48, 0));
//    ogreNode2->attachObject(ogreEntity2);
//    Ogre::Entity *head= mSceneMgr->createEntity("Tete", "ogrehead.mesh");
//
//    Ogre::Entity *ninja = mSceneMgr->createEntity("ninja", "ninja.mesh");
//    Ogre::SceneNode *node= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeTete", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
//    node->attachObject(head);
//    node->attachObject(ninja);
//
//    mSceneMgr->setAmbientLight(Ogre::ColourValue(259.0, 250.0, 250.0));
//    Light *light = mSceneMgr->createLight("lumiere1");
//    light->setDiffuseColour(1.0, 0.7, 1.0);
//    light->setSpecularColour(1.0, 0.7, 1.0);
//    light->setPosition(-100, 200, 100);
//    node->attachObject(light);
//    Ogre::Plane plan(Ogre::Vector3::UNIT_Y, 0);
//    Ogre::MeshManager::getSingleton().createPlane("sol", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 500, 500, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
//    Ogre::Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");
//    ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//    ent->setMaterialName("Ogre/Skin");
//    ogreNode->attachObject(ent);

    // create your scene here :)
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;
         try {
            app.go();
         } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
