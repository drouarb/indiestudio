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
        if (items->itemList.size() != 0)
            itemList = items->itemList;
        return ;
    }
    itemList.merge(items->itemList, Item::compare);
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

    std::cerr << "this:" << this->itemList.size() << " itemcont:" << itemContainer->itemList.size() << std::endl;
    if (itemContainer->itemList.size() > 0)
    {
    this->itemList = std::list<Item> (itemContainer->itemList.size());
    this->itemList = itemContainer->itemList;
    std::cerr << "this:" << this->itemList.size() << " itemcont:" << itemContainer->itemList.size() << std::endl;
    std::cerr << "this:" << this->itemList.front().getName() << this->itemList.front().getId() << " itemcont:" << itemContainer->itemList.front().getName() << itemContainer->itemList.front().getId() << std::endl;
    }
}





