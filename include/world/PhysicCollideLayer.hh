//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Sat May 28 16:21:26 2016 Alexis Trouve
//

#pragma once

#include <tuple>

namespace gauntlet {
    namespace world {
        class PhysicCollideLayer {
        private:
	  double		sizeX;
	  double		sizeY;
	  unsigned char		*layer;
        public:
	  PhysicCollideLayer(const std::string& filePath);

	  ~PhysicCollideLayer();

	  std::pair<double, double> getSize()const;

	  bool isWall(const std::pair<double, double>& oldPos,
		      const std::pair<double, double>& wantedPos);
	  
	  bool checkCoordSizeCanPass(const std::pair<double, double>& oldPos,
				     const std::pair<double, double>& wantedPos,
				     const std::pair<double, double>& size);

	  const unsigned char *getLayer(int nb) const;
        };
    };
};

std::ostream &operator<<(std::ostream &stream, const gauntlet::world::PhysicCollideLayer &p);
