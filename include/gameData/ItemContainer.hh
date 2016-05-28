//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ITEMCONTAINER_HH
# define CPP_INDIE_STUDIO_ITEMCONTAINER_HH

#include <list>
#include "Item.hh"

namespace gauntlet
{
    class Player;
    class ItemContainer
    {
      std::list <Item> itemList;
    public:
      ItemContainer();
      ~ItemContainer();

        std::list<Item> *getItemList();
        void    remove(Item item);
        void operator+=(gauntlet::Player *player);
        void useUpgrades(Player *player);
        ItemContainer *clone(ItemContainer *itemContainer);

        void operator+=(ItemContainer *items);
    };
};


#endif //CPP_INDIE_STUDIO_ITEMCONTAINER_HH
