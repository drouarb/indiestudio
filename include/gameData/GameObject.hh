//
// GameObject.hh for GameObject in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:06:15 2016 Alexis Trouve
// Last update Thu May 19 16:15:03 2016 Alexis Trouve
//

#ifndef GAMEOBJECT_HH_
# define GAMEOBJECT_HH_

#include "ContainerObject.hh"
#include "ABody.hh"

namespace gauntlet
{

  namespace	world
  {
    class World;
  }

  class GameObject : public ContainerObject, public ABody
    {
    protected:
      world::World	*world;
      bool          gatherable;
      bool          openable;
      ItemContainer *items;

    public:
      GameObject(int nid, world::World *nworld);
      ~GameObject();

      virtual ABody		*clone(int id) const;
      void open(ItemContainer *curInventory);
      void setBasicParameters(std::string _name, bool _gatherable, bool _openable);
      void addItem(Item item);
      bool gather(Player *player);
  };
};

#endif
