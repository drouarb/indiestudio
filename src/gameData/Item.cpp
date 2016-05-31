//
// Item.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 11:28:38 2016 Alexis Trouve
// Last update Mon May  9 16:02:21 2016 Alexis Trouve
//

#include <iostream>
#include "Item.hh"

using namespace gauntlet;

gauntlet::Item::Item()
{
    consumable = false;
    upgrade = false;
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

std::string gauntlet::Item::getName() {
    return this->name;
}

Stats   *gauntlet::Item::modifyStats() {
    return &this->stats;
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

bool    gauntlet::Item::compare(Item item, Item item2)
{
    return (true);
}

bool    gauntlet::Item::operator<(Item item)
{
    return (false);
}

bool    gauntlet::Item::isKey() {
    return key;
}

void gauntlet::Item::setKey(bool _key) {
    key = _key;
}

void gauntlet::Item::setId() {
    this->id = getNewId();
}

void gauntlet::Item::setPrice(int _price) {
    price = _price;
}

void Item::setAsConsummable() {
    consumable = true;
}





