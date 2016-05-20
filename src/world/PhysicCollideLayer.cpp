//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Wed May 18 17:19:07 2016 Alexis Trouve
//

#include <iostream>
#include "world/PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(double sizex, double sizey) : sizeX(sizex), sizeY(sizey) {
    this->_data = new char[static_cast<int>(sizex * sizey)];
}

PhysicCollideLayer::~PhysicCollideLayer() {

}

std::pair<double, double>    PhysicCollideLayer::getSize() const {
    return (std::make_pair(this->sizeX, this->sizeY));
}

void PhysicCollideLayer::setWall(double x, double y) {
    if (x > this->sizeX || y > this->sizeY || x < 0 || y < 0) {
        throw std::out_of_range("Out of range");
    }
    std::cout << "setWall at x: " << x << " and y: " << y << " <=> _data[" <<
    static_cast<int>(y) * static_cast<int>(this->sizeX) + static_cast<int>(x) << "]" << std::endl;
    this->_data[static_cast<int>(y) * static_cast<int>(this->sizeX) + static_cast<int>(x)] = 1;
}

void    PhysicCollideLayer::setWall(double xpos, double ypos, double xsize, double ysize) {
    for (size_t i = (static_cast<int>(xsize) % 2), pos_x = xpos - xpos / 2 + 1; i < static_cast<int>(xsize) + 1; ++i) {
        for (size_t j = (static_cast<int>(ysize) % 2), pos_y = ypos - ypos / 2 + 1; j < static_cast<int>(ysize) + 1; ++j) {
            this->setWall(pos_x + i, pos_y + j);
        }
    }
}

void PhysicCollideLayer::unsetWall(double x, double y) {
    if (x > this->sizeX || y > this->sizeY || x < 0 || y < 0) {
        throw std::out_of_range("Out of range");
    }
    this->_data[static_cast<int>(y) * static_cast<int>(this->sizeX) + static_cast<int>(x)] = 0;
}

bool PhysicCollideLayer::isWall(unsigned int x, unsigned int y) {
    if (x > this->sizeX || y > this->sizeY || x < 0 || y < 0) {
        throw std::out_of_range("Out of range");
    }
    return (this->_data[static_cast<int>(y * this->sizeX + x)] == 1);
}

void    PhysicCollideLayer::unsetWall(double xpos, double ypos, double xsize, double ysize) {
    for (size_t i = 0, pos_x = xpos - xpos / 2 + 1; i < static_cast<int>(xsize) + 1; ++i) {
        for (size_t j = 0, pos_y = ypos - ypos / 2 + 1; j < static_cast<int>(ysize) + 1; ++j) {
            this->unsetWall(pos_x + i, pos_y + j);
        }
    }
}

bool    PhysicCollideLayer::checkCoordSize(double xpos, double ypos, double xsize, double ysize) {
    for (size_t i = 0, pos_x = xpos - xpos / 2 + 1; i < static_cast<int>(xsize) + 1; ++i) {
        for (size_t j = 0, pos_y = ypos - ypos / 2 + 1; j < static_cast<int>(ysize) + 1; ++j) {
            if (this->isWall(pos_x + i, pos_y + j)) {
                return true;
            }
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const PhysicCollideLayer &p) {
    const std::pair<double, double> &pair = p.getSize();
    double sizeX = pair.first;
    double sizeY = pair.second;
    const char *_data = p.getData();

    size_t d = static_cast<size_t>(sizeX * sizeY);
    for (size_t i = 0; i < d; ++i) {
        if (i != 0 && (i) % static_cast<int>(sizeX) == 0) {
            stream << std::endl;
        }
        stream << (_data[i] == 0 ? "0" : "1");

    }
    stream << std::endl;
    return stream;
}


const char *PhysicCollideLayer::getData() const {
    return _data;
}