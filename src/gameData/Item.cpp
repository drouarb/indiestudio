//
// Item.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 11:28:38 2016 Alexis Trouve
// Last update Mon May  9 16:02:21 2016 Alexis Trouve
//

#include "Item.hh"

using namespace gauntlet;

gauntlet::Item::Item()
{
}

gauntlet::Item::~Item()
{
}

Stats   gauntlet::Item::getStats() {
    return this->stats;
}

bool    gauntlet::Item::isConsumable() {
    return this->consumable;
}

bool    gauntlet::Item::operator==(Item item)
{
    return this->id == item.id;
}