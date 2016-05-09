//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HH
#define CPP_INDIE_STUDIO_PLAYER_HH

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

class Player : public Actor
{
private:
  std::string			playerName;
  long				score;
  ItemContainer			inventory;
};


#endif //CPP_INDIE_STUDIO_PLAYER_HH
