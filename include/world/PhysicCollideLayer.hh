//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Tue May 31 15:18:57 2016 Esteban Lewis
//

#pragma once

#include <tuple>
#include "HeightMap.hh"

# define WALL_MIN_HEIGHT 40
# define ABS(x) ((x) < 0 ? -(x) : (x))

namespace gauntlet {
    namespace world {
        class PhysicCollideLayer {
        private:
	  double			sizeX;
	  double			sizeY;
	  unsigned char			*layer;
	  HeightMap			heightmap;
	  std::pair<double, double>	inc;
	  int				nb_points;
	  std::pair<double, double>	lastPoint;
	private:
	  bool				doOnLine(std::pair<double, double> start, std::pair <double, double> end,
						 bool (PhysicCollideLayer::*func)(std::pair<double, double>));
	  bool				checkLine(std::pair<double, double> point);
	  bool				checkPoint(std::pair<double, double> point);
        public:
	  PhysicCollideLayer(const std::string& filePath);

	  ~PhysicCollideLayer();

	  std::pair<double, double>	getSize()const;

	  bool				isWall(const std::pair<double, double>& oldPos,
					       const std::pair<double, double>& wantedPos);

	  bool				checkCoordSizeCanPass(const std::pair<double, double>& oldPos,
							      const std::pair<double, double>& wantedPos,
							      const std::pair<double, double>& size);
	  bool				checkDiagonal(std::pair<double, double> start,
						      std::pair<double, double> end,
						      std::pair<double, double> oldPos,
						      std::pair<double, double> wantedPos);

	  const unsigned char		*getLayer() const;
        };
    };
};

std::ostream &operator<<(std::ostream &stream, const gauntlet::world::PhysicCollideLayer &p);
