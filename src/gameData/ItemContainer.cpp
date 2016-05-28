//
// Created by jonas_e on 5/9/16.
//

#include "Player.hh"
#include "ItemContainer.hh"

using namespace gauntlet;

ItemContainer::ItemContainer()
{

}

ItemContainer::~ItemContainer()
{

}

void ItemContainer::operator+=(Player *player)
{
    itemList.merge(player->getInventory()->itemList);
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

ItemContainer *ItemContainer::clone(ItemContainer *itemContainer) {
    ItemContainer *newItemContainer;

    newItemContainer = new ItemContainer();
    newItemContainer->itemList = itemContainer->itemList;
    return newItemContainer;
}





