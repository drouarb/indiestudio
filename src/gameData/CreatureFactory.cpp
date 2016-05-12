//
// CreatureFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 19:05:59 2016 Alexis Trouve
// Last update Thu May 12 17:12:54 2016 Alexis Trouve
//

#include "CreatureFactory.hh"

using namespace gauntlet;

CreatureFactory::CreatureFactory()
{
  fillCreatureTab();
}

CreatureFactory::~CreatureFactory()
{

}

void		CreatureFactory::fillCreatureTab()
{
  creatureTab.push_back({MOMIE, &CreatureFactory::giveMomie});
}

Creature	*CreatureFactory::giveMomie(int id)
{
  Creature	*creature;

  creature = new Creature(id, -1, -1, SIZE_X_CREATURE_T1, SIZE_Y_CREATURE_T1, 0);
  return (creature);
}

Creature	*CreatureFactory::giveCreature(BodyEnum type, int id)
{
  unsigned int		i;

  i = 0;
  while (i < creatureTab.size())
    {
      if (creatureTab[i].type == type)
	return ((this->*creatureTab[i].givePtr)(id));
      ++i;
    }
  return (NULL);
}
