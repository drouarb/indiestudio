//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Mon May 16 16:22:25 2016 Alexis Trouve
//

#pragma once

#include <tuple>

static const int BIT_IN_BYTE = 8;
namespace gauntlet {
    namespace world {
        class PhysicCollideLayer {
        private:
            double sizeX;
            double sizeY;
            char *_data;
        public:
            PhysicCollideLayer(double sizeX, double sizeY);

            ~PhysicCollideLayer();

            std::pair<double, double> getSize();

            void setWall(int x, int y);

            bool isWall(int x, int y);


        };
    };
};
