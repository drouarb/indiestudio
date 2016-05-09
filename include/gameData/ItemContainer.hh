//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ITEMCONTAINER_HH
#define CPP_INDIE_STUDIO_ITEMCONTAINER_HH

#include <list>
#include "Item.hh"

namespace gauntlet {
    class ItemContainer {
    private:
        std::list <Item> itemList;
    public:
        void    remove(Item item);
    };
};


#endif //CPP_INDIE_STUDIO_ITEMCONTAINER_HH
