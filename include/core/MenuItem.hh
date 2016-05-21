//
// Created by celeri on 5/19/16.
//

#ifndef OGREAPP_MENUITEM_HH
#define OGREAPP_MENUITEM_HH

#include <string>

namespace				gauntlet
{
    namespace core {

        enum MenuItemType
        {
            BUTTON,
            SELECTMENU,
            LABEL,
            SLIDE,
            PROGRESSBAR,
            CHECKBOX,
            TEXTBOX,
            DIALOGBOX,
        };
        enum MenuCheckBoxState
        {
            CHECKED,
            NOCHECKED
        };
        struct t_hitItem
        {
            MenuItemType type;
            int value;
            std::string data;
            MenuCheckBoxState state;
        };
    };
};
#endif //OGREAPP_MENUITEM_HH
