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
    consumable = false;
    id = getNewId();
}

gauntlet::Item::~Item()
{
}

void     gauntlet::Item::generateItem(int pf) {
    price = 100 * pf;
    name = "Shiny stuff";
}

int     gauntlet::Item::getNewId() {
    static int  i = 0;
    return (i++);
}

bool    gauntlet::Item::isUpgrade() {
    return upgrade;
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

bool    gauntlet::Item::operator<(Item item)
{
    return true; //ne modifie pas l'ordre pour merge. sujet à changement.
}

bool    gauntlet::Item::isKey() {
    return key;
}

void Item::setKey(bool _key) {
    key = _key;
}



