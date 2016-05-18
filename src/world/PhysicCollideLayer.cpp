//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Sat May 14 12:12:55 2016 Alexis Trouve
//

#include "PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(double sizex, double sizey) {
    this->sizeX = sizex;
    this->sizeY = sizey;
    this->_data = new char[sizex * sizey / BIT_IN_BYTE];
}

PhysicCollideLayer::~PhysicCollideLayer() {

}

std::pair<double, double>    PhysicCollideLayer::getSize() {
    return (std::make_pair(this->sizeX, this->sizeY));
}

void PhysicCollideLayer::setWall(int x, int y) {
    int i = (x * y) / BIT_IN_BYTE;
    this->_data[i] ^= (-x ^ this->_data[i]) & (1 << ((x * y) % BIT_IN_BYTE));
}

bool PhysicCollideLayer::isWall(int x, int y) {
    return ((this->_data[x * y / BIT_IN_BYTE] >> ((x * y) % BIT_IN_BYTE)) & 1) == 1;
}