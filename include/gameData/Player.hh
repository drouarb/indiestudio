//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HH
# define CPP_INDIE_STUDIO_PLAYER_HH

#include <string>
#include "Actor.hh"
#include "ItemContainer.hh"

enum	itemSlot
  {
    CHEST,
    HEAD,
    FEET,
    EQUIPMENT
  };

namespace gauntlet
{

  class Actor;

    class Player : public Actor
    {
    private:
      std::string playerName;
      long score;
      ItemContainer inventory;
    public:
      Player(bool collide, int nid, double posx,
	     double posy, double sizex, double sizey, short norient);
      Player(int nid, double posx, double posy, double sizex,
	     double sizey, short norient);
      ~Player();
      void addScore(long addition);
      // void equip(Item item);
      void use(Item item);
    };
}

#endif //CPP_INDIE_STUDIO_PLAYER_HH
