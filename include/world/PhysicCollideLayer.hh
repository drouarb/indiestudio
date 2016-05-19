//
// PhysicCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:15:29 2016 Alexis Trouve
// Last update Thu May 19 09:40:38 2016 Alexis Trouve
//

#pragma once

#include <tuple>

static const int BIT_IN_BYTE = 8;
namespace gauntlet
{
    namespace world
    {
      class PhysicCollideLayer {
      private:
	double sizeX;
	double sizeY;
	char *_data;
      public:
	PhysicCollideLayer(double sizeX, double sizeY);
	
	~PhysicCollideLayer();
	
	std::pair<double, double> getSize();
	
	void	setWall(unsigned int x, unsigned int y);
	void	unsetWall(unsigned int x, unsigned int y);
	
	bool	isWall(unsigned int x, unsigned int y);
	
	void	setWallWithSize(double xpos, double ypos, double xsize, double ysize);
	void	unsetWallWithSize(double xpos, double ypos, double xsize, double ysize);
	
	bool	checkCoordSize(double xpos, double ypos, double xsize, double ysize);

        };
    };
};
