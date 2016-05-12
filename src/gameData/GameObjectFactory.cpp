//
// GameObjectFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 19:05:59 2016 Alexis Trouve
// Last update Thu May 12 16:50:40 2016 Alexis Trouve
//

#include "GameObjectFactory.hh"

using namespace gauntlet;

GameObjectFactory::GameObjectFactory()
{
  fillGameObjectTab();
}

GameObjectFactory::~GameObjectFactory()
{

}

void		GameObjectFactory::fillGameObjectTab()
{
  gameObjectTab.push_back({BROKINGWALLVERTICAL, &GameObjectFactory::giveBrokingWallVertical});
}

GameObject	*GameObjectFactory::giveBrokingWallVertical(int id)
{
  GameObject	*gameObject;

  gameObject = new GameObject(id, -1, -1, SIZE_X_BROKINGWALLVERTICAL, SIZE_Y_BROKINGWALLVERTICAL, 0);
  return (gameObject);
}

GameObject	*GameObjectFactory::giveGameObject(BodyEnum type, int id)
{
  unsigned int		i;

  i = 0;
  while (i < gameObjectTab.size())
    {
      if (gameObjectTab[i].type == type)
	return ((this->*gameObjectTab[i].givePtr)(id));
      ++i;
    }
  return (NULL);
}
