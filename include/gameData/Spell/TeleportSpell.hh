//
// TeleportSpell.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 11:05:51 2016 Alexis Trouve
// Last update Sat May 14 15:33:32 2016 Alexis Trouve
//

#ifndef CPP_INDIE_STUDIO_TELEPORTSPELL_HH
# define CPP_INDIE_STUDIO_TELEPORTSPELL_HH

#include <string>
#include "World.hh"
#include "DistAttack.hh"

namespace gauntlet
{
  class TeleportSpell : public DistAttack
    {
    public:
      TeleportSpell(bool nbump, long ndamage, short nangle,
		    short nnbrProj, double nrange, double nradiusExplode,
		    int nid, const std::string &nname, double ncastTime);
      ~TeleportSpell();
      virtual void	 apply(double orientation, world::World &world,
			       gauntlet::Actor *SpellCaster,
			       std::pair<double, double> coordPointed);
    };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
