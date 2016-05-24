//
// Created by drouar_b on 5/24/16.
//

#include <OIS/OIS.h>
#include "graph/OgreUI.hh"

const std::map<OIS::KeyCode, gauntlet::core::IUIObserver::Key> OgreUI::keymap = {
        {OIS::KC_UP,        gauntlet::core::IUIObserver::KEY_UP},
        {OIS::KC_DOWN,      gauntlet::core::IUIObserver::KEY_DOWN},
        {OIS::KC_RIGHT,     gauntlet::core::IUIObserver::KEY_RIGHT},
        {OIS::KC_LEFT,      gauntlet::core::IUIObserver::KEY_LEFT},
        {OIS::KC_ESCAPE,    gauntlet::core::IUIObserver::KEY_ESC},
        {OIS::KC_TAB,       gauntlet::core::IUIObserver::KEY_TAB},
        {OIS::KC_SPACE,     gauntlet::core::IUIObserver::KEY_SPACE},
        {OIS::KC_BACK,      gauntlet::core::IUIObserver::KEY_BACK},
        {OIS::KC_A,         gauntlet::core::IUIObserver::KEY_A},
        {OIS::KC_B,         gauntlet::core::IUIObserver::KEY_B},
        {OIS::KC_C,         gauntlet::core::IUIObserver::KEY_C},
        {OIS::KC_D,         gauntlet::core::IUIObserver::KEY_D},
        {OIS::KC_E,         gauntlet::core::IUIObserver::KEY_E},
        {OIS::KC_F,         gauntlet::core::IUIObserver::KEY_F},
        {OIS::KC_RETURN,    gauntlet::core::IUIObserver::KEY_ENTER},
        {OIS::KC_G,         gauntlet::core::IUIObserver::KEY_G},
        {OIS::KC_H,         gauntlet::core::IUIObserver::KEY_H},
        {OIS::KC_I,         gauntlet::core::IUIObserver::KEY_I},
        {OIS::KC_J,         gauntlet::core::IUIObserver::KEY_J},
        {OIS::KC_K,         gauntlet::core::IUIObserver::KEY_K},
        {OIS::KC_L,         gauntlet::core::IUIObserver::KEY_L},
        {OIS::KC_M,         gauntlet::core::IUIObserver::KEY_M},
        {OIS::KC_N,         gauntlet::core::IUIObserver::KEY_N},
        {OIS::KC_O,         gauntlet::core::IUIObserver::KEY_O},
        {OIS::KC_P,         gauntlet::core::IUIObserver::KEY_P},
        {OIS::KC_Q,         gauntlet::core::IUIObserver::KEY_Q},
        {OIS::KC_R,         gauntlet::core::IUIObserver::KEY_R},
        {OIS::KC_S,         gauntlet::core::IUIObserver::KEY_S},
        {OIS::KC_T,         gauntlet::core::IUIObserver::KEY_T},
        {OIS::KC_U,         gauntlet::core::IUIObserver::KEY_U},
        {OIS::KC_V,         gauntlet::core::IUIObserver::KEY_V},
        {OIS::KC_W,         gauntlet::core::IUIObserver::KEY_W},
        {OIS::KC_X,         gauntlet::core::IUIObserver::KEY_X},
        {OIS::KC_Y,         gauntlet::core::IUIObserver::KEY_Y},
        {OIS::KC_Z,         gauntlet::core::IUIObserver::KEY_Z},

        {OIS::KC_0,         gauntlet::core::IUIObserver::KEY_0},
        {OIS::KC_1,         gauntlet::core::IUIObserver::KEY_1},
        {OIS::KC_2,         gauntlet::core::IUIObserver::KEY_2},
        {OIS::KC_3,         gauntlet::core::IUIObserver::KEY_3},
        {OIS::KC_4,         gauntlet::core::IUIObserver::KEY_4},
        {OIS::KC_5,         gauntlet::core::IUIObserver::KEY_5},
        {OIS::KC_6,         gauntlet::core::IUIObserver::KEY_6},
        {OIS::KC_7,         gauntlet::core::IUIObserver::KEY_7},
        {OIS::KC_8,         gauntlet::core::IUIObserver::KEY_8},
        {OIS::KC_9,         gauntlet::core::IUIObserver::KEY_9},

        {OIS::KC_NUMPAD0,   gauntlet::core::IUIObserver::KEY_0},
        {OIS::KC_NUMPAD1,   gauntlet::core::IUIObserver::KEY_1},
        {OIS::KC_NUMPAD2,   gauntlet::core::IUIObserver::KEY_2},
        {OIS::KC_NUMPAD3,   gauntlet::core::IUIObserver::KEY_3},
        {OIS::KC_NUMPAD4,   gauntlet::core::IUIObserver::KEY_4},
        {OIS::KC_NUMPAD5,   gauntlet::core::IUIObserver::KEY_5},
        {OIS::KC_NUMPAD6,   gauntlet::core::IUIObserver::KEY_6},
        {OIS::KC_NUMPAD7,   gauntlet::core::IUIObserver::KEY_7},
        {OIS::KC_NUMPAD8,   gauntlet::core::IUIObserver::KEY_8},
        {OIS::KC_NUMPAD9,   gauntlet::core::IUIObserver::KEY_9},
        {OIS::KC_PERIOD,    gauntlet::core::IUIObserver::KEY_PERIOD},
        {OIS::KC_SEMICOLON, gauntlet::core::IUIObserver::KEY_PERIOD}
};

const std::map<OIS::MouseButtonID, gauntlet::core::IUIObserver::Key> OgreUI::mousemap = {
        {OIS::MB_Left,  gauntlet::core::IUIObserver::KEY_MOUSE1},
        {OIS::MB_Right, gauntlet::core::IUIObserver::KEY_MOUSE2}
};

const std::map<gauntlet::core::Position, OgreBites::TrayLocation> OgreUI::posmap = {
        {gauntlet::core::PCENTER,      OgreBites::TL_CENTER},
        {gauntlet::core::PTOPRIGHT,    OgreBites::TL_TOPRIGHT},
        {gauntlet::core::PTOPLEFT,     OgreBites::TL_TOPLEFT},
        {gauntlet::core::PTOP,         OgreBites::TL_TOP},
        {gauntlet::core::PBOTTOM,      OgreBites::TL_BOTTOM},
        {gauntlet::core::PBOTTOMLEFT,  OgreBites::TL_BOTTOMLEFT},
        {gauntlet::core::PBOTTOMRIGHT, OgreBites::TL_BOTTOMRIGHT},
        {gauntlet::core::PRIGHT,       OgreBites::TL_RIGHT},
        {gauntlet::core::PLEFT,        OgreBites::TL_LEFT}
};

const std::map<gauntlet::EntityName, std::string> OgreUI::meshmap = {
        {gauntlet::EntityName::OGREHEAD,     "Troll_2_H_FBX.mesh"},
        {gauntlet::EntityName::NINJA,        "ninja.mesh"},
        {gauntlet::EntityName::PLAN,         "plan.mesh"},
        {gauntlet::EntityName::TUDORHOUSE,   "tudorhouse.mesh"},
        {gauntlet::EntityName::DOOR,         "door.mesh"},
        {gauntlet::EntityName::CUBE,         "cube.mesh"},
        {gauntlet::EntityName::ROCK,         "Rock.mesh"},
        {gauntlet::EntityName::CHEST,        "chest.mesh"},
        {gauntlet::EntityName::CHESTCARTOON, "chestCartoon.mesh"},
        {gauntlet::EntityName::WAGEN,        "wagen.mesh"}
};

const std::map<gauntlet::Texturename, std::string> OgreUI::texturemap = {
        {gauntlet::Texturename::NINjA_M,      "Ogre/Skin"},
        {gauntlet::Texturename::TUDORHOUSE_M, "TudorHouse/house"}
};
