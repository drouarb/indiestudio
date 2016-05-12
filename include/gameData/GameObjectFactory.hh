//
// GameObjectFactory.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 18:36:12 2016 Alexis Trouve
// Last update Thu May 12 16:52:42 2016 Alexis Trouve
//

#ifndef GAMEOBJFACT_HH_
# define GAMEOBJFACT_HH_

#include <vector>
#include "FactoryData.hh"
#include "GameObject.hh"

namespace gauntlet
{

  class	GameObjectFactory;
  
  struct	GameObjectStruct
  {
    gauntlet::BodyEnum		type;
    gauntlet::GameObject	*(gauntlet::GameObjectFactory::*givePtr)(int id);
  };

  class	GameObjectFactory
  {
  private:
    std::vector<GameObjectStruct>	gameObjectTab;
  private:
    void			fillGameObjectTab();

    gauntlet::GameObject	*giveBrokingWallVertical(int id);
  public:
    GameObjectFactory();
    ~GameObjectFactory();
    gauntlet::GameObject	*giveGameObject(gauntlet::BodyEnum type, int id);
  };
};

#endif
