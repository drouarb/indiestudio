//
// Created by jonas_e on 5/9/16.
//

#include <iostream>
#include "Player.hh"
#include "ItemContainer.hh"

using namespace gauntlet;

ItemContainer::ItemContainer()
{
    itemList = std::list<Item>();
}

ItemContainer::~ItemContainer()
{

}

void ItemContainer::operator+=(ItemContainer *items)
{
    if (itemList.size() == 0)
    {
        std::cout << itemList.size() << std::endl;
        std::cout << items->itemList.size() << std::endl;
        if (items->itemList.size() != 0)
            itemList = items->itemList;
        return ;
    }
    itemList.merge(items->itemList, Item::compare);
    std::cout << "oky" << std::endl;
}

void ItemContainer::remove(gauntlet::Item item) {
    this->itemList.remove(item);
}

std::list<Item> *ItemContainer::getItemList() {
    return &this->itemList;
}

void ItemContainer::useUpgrades(Player *player) {
    std::list<Item>::iterator iter;
    for(iter = this->itemList.begin(); iter != this->itemList.end(); ++iter)
    {
        if (iter->isUpgrade())
        {
            player->use(*iter);
            iter = this->itemList.erase(iter);
        }
    }
}

void        ItemContainer::clone(ItemContainer *itemContainer) {

    this->itemList = itemContainer->itemList;
}





