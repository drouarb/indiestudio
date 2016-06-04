//
// BasicAI.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:46:42 2016 Alexis Trouve
// Last update Sat Jun  4 18:50:36 2016 Alexis Trouve
//

#include <iostream>
#include "AbstractAI.hh"
#include "World.hh"

using namespace gauntlet;
using namespace world;

AbstractAI::AbstractAI(World *nworld)
{
  std::cout << "AI INSTANCIER" << std::endl;
  world = nworld;
  nameAI = "nothing";
}

AbstractAI::~AbstractAI()
{
}

bool		AbstractAI::setNewAI(gauntlet::Actor *actor)
{
  unsigned int	i;

  i = 0;
  std::cout << "nameAI : " << nameAI << std::endl;
  std::cout << "actor " << actor->getId() << " name:" << actor->getName() << std::endl;
  while (i < actors.size())
    {
      if (actors[i]->getId() == actor->getId())
	return (false);
      ++i;
    }
  actors.push_back(actor);
  return (true);
}

void		AbstractAI::suprActor(int id)
{
  unsigned int	i;

  i = 0;
  while (i < actors.size())
    {
      if (actors[i]->getId() == id)
	{
	  actors.erase(actors.begin() + i);
	  return ;
	}
      ++i;
    }
}

const std::string&	AbstractAI::getName() const
{
  return (nameAI);
}
