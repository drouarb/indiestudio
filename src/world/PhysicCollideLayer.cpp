//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Wed May 18 17:19:07 2016 Alexis Trouve
//

#include "PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(double sizex, double sizey) {
    this->sizeX = sizex;
    this->sizeY = sizey;
    int d = sizex * sizey / BIT_IN_BYTE;
    this->_data = new char[d];
}

PhysicCollideLayer::~PhysicCollideLayer() {

}

std::pair<double, double>    PhysicCollideLayer::getSize() {
    return (std::make_pair(this->sizeX, this->sizeY));
}

void PhysicCollideLayer::setWall(unsigned int x, unsigned int y) {
    unsigned int i = (x * y) / BIT_IN_BYTE;
    this->_data[i] ^= (-x ^ this->_data[i]) & (1 << ((x * y) % BIT_IN_BYTE));
}

void PhysicCollideLayer::unsetWall(unsigned int x, unsigned int y) {
}

bool PhysicCollideLayer::isWall(unsigned int x, unsigned int y) {
    return ((this->_data[x * y / BIT_IN_BYTE] >> ((x * y) % BIT_IN_BYTE)) & 1) == 1;
}

void	PhysicCollideLayer::setWallWithSize(double xpos, double ypos, double xsize, double ysize)
{

}

void	PhysicCollideLayer::unsetWallWithSize(double xpos, double ypos, double xsize, double ysize)
{

}

bool	PhysicCollideLayer::checkCoordSize(double xpos, double ypos, double xsize, double ysize)
{

}
