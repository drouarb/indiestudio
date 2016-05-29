//
// Collider.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 29 20:40:50 2016 Alexis Trouve
// Last update Sun May 29 20:51:25 2016 Alexis Trouve
//

#include <iostream>
#include <stdexcept>
#include "Collider.hh"
#include "Rand.hh"

using namespace gauntlet;
using namespace world;

Collider::Collider(const std::string& filePath)
{
  physicLayer = new PhysicCollideLayer(filePath);
  sizeX = physicLayer->getSize().first;
  sizeY = physicLayer->getSize().second;
  if (sizeX < SIZE_CASE || sizeY < SIZE_CASE)
    throw std::runtime_error("Map size too small");
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
  if (physicLayer->checkCoordSizeCanPass(body->getPos(), std::make_pair(posx, posy), body->getSize()) == false)
    return (false);
  return (dynamicLayer->tryMoveId(id, posx, posy));
}

bool	Collider::forceMoveBody(int id, double posx, double posy)
{
  dynamicLayer->forceMoveId(id, posx, posy);
  return (true);
}

void				Collider::autoShift()
{
  std::cout << "autoshift" << std::endl;
  std::list<ABody*>		collideEntity;
  std::list<ABody*>::iterator	it;
  int				orient;
  double			vectX;
  double			vectY;

  collideEntity = dynamicLayer->getCollideBody();
  it = collideEntity.begin();
  while (it != collideEntity.end())
    {
      orient = Rand::generate() % 628;
      vectY = (Math::sin(orient) * (*it)->getSize().second / 2.0);
      vectX = (Math::cos(orient) * (*it)->getSize().first / 2.0);
      if (physicLayer->checkCoordSizeCanPass((*it)->getPos(),
					     std::make_pair((*it)->getPos().first + vectX, (*it)->getPos().second),
					     (*it)->getSize()) != false)
	dynamicLayer->forceMoveId((*it)->getId(), (*it)->getPos().first + vectX, (*it)->getPos().second);
      if (physicLayer->checkCoordSizeCanPass((*it)->getPos(),
					     std::make_pair((*it)->getPos().first, (*it)->getPos().second + vectY),
					     (*it)->getSize()) != false)
	dynamicLayer->forceMoveId((*it)->getId(), (*it)->getPos().first, (*it)->getPos().second + vectY);
      it++;
    }
  std::cout << "autoshift" << std::endl;
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
  tryMoveBody(id, posB.first + vectX, posB.second);
  posB = body->getPos();
  tryMoveBody(id, posB.first, posB.second + vectY);
  return (true);
}

bool	Collider::setNewBody(ABody *body)
{
  return (dynamicLayer->setNewBody(body));
}

void	Collider::setNewBodyNoCheckEntity(ABody *body)
{
  dynamicLayer->forceSetBody(body);
}

void	Collider::suprBody(int id)
{
  dynamicLayer->suprId(id);
}

std::list<ABody*>		Collider::suprCoordInList(double posx, double posy, std::list<ABody*> list)
{
  std::list<gauntlet::ABody*>		newlist;
  std::list<gauntlet::ABody*>::iterator	it;

  it = list.begin();
  while (it != list.end())
    {
      if ((*it)->getPos().first != posx && (*it)->getPos().second != posy)
	newlist.push_back((*it));
      ++it;
    }
  return (newlist);
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCircle(double posx, double posy, short unused,
							       double radius, short unused2)
{
  (void)unused;
  (void)unused2;
  return (suprCoordInList(posx, posy, dynamicLayer->giveBodyInAreaCircle(posx, posy, radius)));
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  return (suprCoordInList(posx, posy, dynamicLayer->giveBodyInAreaCone(posx, posy, ref_angle, size, cone_angle)));
}

std::list<gauntlet::ABody*>	Collider::giveBodyInAreaflightPath(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  std::list<gauntlet::ABody*>	list;
  std::list<gauntlet::ABody*>	returnList;
  std::list<gauntlet::ABody*>::iterator	it;
  std::list<gauntlet::ABody*>::iterator	itrem;;

  list = dynamicLayer->giveBodyInAreaCone(posx, posy, ref_angle, size, cone_angle);
  if (list.size() == 0)
    return (returnList);
  list = suprCoordInList(posx, posy, list);
  it = list.begin();
  itrem = list.begin();
  while (it != list.end())
    {
      if (Math::distBetween((*it)->getPos(), std::make_pair(posx, posy))
	  < Math::distBetween((*itrem)->getPos(), std::make_pair(posx, posy)))
	itrem = it;
      it++;
    }
  returnList.push_back(*itrem);
  return (returnList);
}

std::pair<unsigned int, unsigned int>	Collider::getSizeMap() const
{
  return (std::make_pair(sizeX, sizeY));
}

double					Collider::getDist(double ref_x, double ref_y,
							  const ABody &target)
{
  return (dynamicLayer->getDist(ref_x, ref_y, target));
}
