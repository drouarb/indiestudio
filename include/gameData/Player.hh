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
    protected:

      std::string playerName;
      long score;
      ItemContainer inventory;
    public:
      Player(int nid, world::World *newWorld);
      ~Player();

      void			        addScore(long addition);
      void			        setPlayerName(const std::string& nplayerName);
      const std::string&	getPlayerName() const;
      long			        getScore() const;
      // void equip(Item item);
      void			        use(Item item);
      virtual ABody		    *clone(int id) const;
    };
}

#endif //CPP_INDIE_STUDIO_PLAYER_HH
