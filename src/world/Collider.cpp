//
// Collider.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:44:15 2016 Alexis Trouve
// Last update Wed May 18 11:45:41 2016 Alexis Trouve
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
  return (dynamicLayer->tryMoveId(id, posx, posy));
}

bool	Collider::setNewBody(ABody *body)
{
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
