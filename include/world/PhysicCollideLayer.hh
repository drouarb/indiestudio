//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Wed May 18 17:05:31 2016 Alexis Trouve
//

#pragma once

#include <tuple>

namespace gauntlet {
    namespace world {
        class PhysicCollideLayer {
        private:
            static const int BIT_IN_BYTE = 8;
            const double sizeX;
            const double sizeY;
            char *_data;
        public:
            PhysicCollideLayer(double sizeX, double sizeY);

            ~PhysicCollideLayer();

            std::pair<double, double> getSize()const;

            void setWall(double x, double y);

            void unsetWall(double x, double y);

            bool isWall(unsigned int x, unsigned int y);

            void setWall(double xpos, double ypos, double xsize, double ysize);

            void unsetWall(double xpos, double ypos, double xsize, double ysize);

            bool checkCoordSize(double xpos, double ypos, double xsize, double ysize);


            const char *getData() const;
        };
    };
};

std::ostream &operator<<(std::ostream &stream, const gauntlet::world::PhysicCollideLayer &p);