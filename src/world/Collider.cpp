//
// Collider.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:44:15 2016 Alexis Trouve
// Last update Thu May 19 10:15:29 2016 Alexis Trouve
//

#include "Collider.hh"

using namespace gauntlet;
using namespace world;

Collider::Collider()
{
  physicLayer = new PhysicCollideLayer(2100.0, 2100.0);
  dynamicLayer = new EntityCollideLayer(physicLayer);
}

Collider::~Collider()
{

}

bool	Collider::tryMoveBody(int id, double posx, double posy)
{
  ABody	*body;

  if ((body = dynamicLayer->getBodyId(id)) == NULL)
    return (false);
  if (physicLayer->checkCoordSize(body->getPos().first, body->getPos().second,
				  body->getSize().first, body->getSize().second) == false)
    return (false);
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
  vectY = (Math::sin(orient) * speed);
  vectX = (Math::cos(orient) * speed);
  sizeB = body->getSize();
  posB = body->getPos();
  if (physicLayer->checkCoordSize(posB.first + vectX, posB.second, sizeB.first, sizeB.second) == false ||
      dynamicLayer->tryMoveId(id, posB.first + vectX, posB.second) == false)
    if (physicLayer->checkCoordSize(posB.first, posB.second + vectY, sizeB.first, sizeB.second) != false)
      dynamicLayer->tryMoveId(id, posB.first, posB.second + vectY);
}

bool	Collider::setNewBody(ABody *body)
{
  if (physicLayer->checkCoordSize(body->getPos().first, body->getPos().second,
				  body->getSize().first, body->getSize().second) == false)
    return (false);
  return (dynamicLayer->setNewBody(body));
}

void	Collider::suprBody(int id)
{
  dynamicLayer->suprId(id);
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCircle(double posx, double posy, double rayon)
{
  return (dynamicLayer->giveBodyInAreaCircle(posx, posy, rayon));
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  return (dynamicLayer->giveBodyInAreaCone(posx, posy, ref_angle, size, cone_angle));
}
