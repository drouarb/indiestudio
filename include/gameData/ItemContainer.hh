//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ITEMCONTAINER_HH
# define CPP_INDIE_STUDIO_ITEMCONTAINER_HH

#include <list>
#include "Item.hh"

namespace gauntlet
{
    class ItemContainer
    {
      std::list <Item> itemList;
    public:
      ItemContainer();
      ~ItemContainer();

        std::list<Item> *getItemList();
      void    remove(Item item);
      void    operator+=(ItemContainer *itemContainer);
    };
};


#endif //CPP_INDIE_STUDIO_ITEMCONTAINER_HH
