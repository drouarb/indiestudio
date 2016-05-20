//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Fri May 20 13:41:59 2016 Alexis Trouve
//

#pragma once

#include <tuple>

namespace gauntlet {
    namespace world {
        class PhysicCollideLayer {
        private:
	  unsigned int		sizeX;
	  unsigned int		sizeY;
	  unsigned char		*layer;
        public:
            PhysicCollideLayer(unsigned int sizeX, unsigned int sizeY);

            ~PhysicCollideLayer();

            std::pair<double, double> getSize()const;

            void setWall(unsigned int x, unsigned int y);

            void unsetWall(unsigned int x, unsigned int y);

            bool isWall(unsigned int x, unsigned int y);

            void setWall(double xpos, double ypos, double xsize, double ysize);

            void unsetWall(double xpos, double ypos, double xsize, double ysize);

            bool checkCoordSize(double xpos, double ypos, double xsize, double ysize);


            const unsigned char *getLayer() const;
        };
    };
};

std::ostream &operator<<(std::ostream &stream, const gauntlet::world::PhysicCollideLayer &p);
