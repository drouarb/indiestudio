//
// Collider.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:44:15 2016 Alexis Trouve
// Last update Sat May 28 16:18:50 2016 Alexis Trouve
//

#include <iostream>
#include <stdexcept>
#include "Collider.hh"

using namespace gauntlet;
using namespace world;

Collider::Collider(const std::string& filePath)
{
  //if (xsize < SIZE_CASE || ysize < SIZE_CASE)
  //throw std::runtime_error("Map size too small");
  physicLayer = new PhysicCollideLayer(filePath);
  dynamicLayer = new EntityCollideLayer(physicLayer);
  //sizeX = xsize;
  //sizeY = ysize;
}

Collider::~Collider()
{

}

bool	Collider::tryMoveBody(int id, double posx, double posy)
{
  ABody	*body;

  if ((body = dynamicLayer->getBodyId(id)) == NULL)
    return (false);
  /*if (physicLayer->checkCoordSizeIsEmpty(body->getPos().first, body->getPos().second,
				  body->getSize().first, body->getSize().second) == false)
				  return (false);*/
  return (dynamicLayer->tryMoveId(id, posx, posy));
}

bool				Collider::applyVectorToId(int id, short orient, double speed)
{
  ABody				*body;
  std::pair<double, double>	sizeB;
  std::pair<double, double>	posB;
  double			vectX;
  double			vectY;

  if ((body = dynamicLayer->getBodyId(id)) == NULL)
    return (false);
  vectY = -(Math::sin(orient) * speed);
  vectX = -(Math::cos(orient) * speed);
  sizeB = body->getSize();
  posB = body->getPos();
  /*if (physicLayer->checkCoordSizeIsEmpty(posB.first + vectX, posB.second, sizeB.first, sizeB.second) == true)
    {*/
      dynamicLayer->tryMoveId(id, posB.first + vectX, posB.second);
      posB = body->getPos();
      /*if (physicLayer->checkCoordSizeIsEmpty(posB.first, posB.second + vectY, sizeB.first, sizeB.second) == true)*/
	dynamicLayer->tryMoveId(id, posB.first, posB.second + vectY);
	//}
  return (true);
}

bool	Collider::setNewBody(ABody *body)
{
  /*if (physicLayer->checkCoordSizeIsEmpty(body->getPos().first, body->getPos().second,
				  body->getSize().first, body->getSize().second) == false)
				  return (false);*/
  return (dynamicLayer->setNewBody(body));
}

bool	Collider::setNewBodyNoCheckEntity(ABody *body)
{
  /*if (physicLayer->checkCoordSizeIsEmpty(body->getPos().first, body->getPos().second,
				  body->getSize().first, body->getSize().second) == false)
				  return (false);*/
  dynamicLayer->forceSetBody(body);
  return (true);
}

void	Collider::suprBody(int id)
{
  dynamicLayer->suprId(id);
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCircle(double posx, double posy, short unused,
							       double radius, short unused2)
{
  (void)unused;
  (void)unused2;
  return (dynamicLayer->giveBodyInAreaCircle(posx, posy, radius));
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  return (dynamicLayer->giveBodyInAreaCone(posx, posy, ref_angle, size, cone_angle));
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaflightPath(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  std::list<gauntlet::ABody*> e_list = dynamicLayer->giveBodyInAreaCone(posx, posy, ref_angle, size, cone_angle); //truc pourri rapide pour test. A modifier.
  while (e_list.size() > 1) //méthode pour test, à changer.
  {
    e_list.pop_back();
  }
  return (e_list);
}

std::pair<unsigned int, unsigned int>	Collider::getSizeMap() const
{
  return (std::make_pair(sizeX, sizeY));
}
