//
// Created by jonas_e on 5/9/16.
//

#include "ItemContainer.hh"

using namespace gauntlet;

ItemContainer::ItemContainer()
{

}

ItemContainer::~ItemContainer()
{

}

void ItemContainer::remove(gauntlet::Item item) {
    this->itemList.remove(item);
}