//
// HealAttack.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 11:05:51 2016 Alexis Trouve
// Last update Tue May 10 17:42:15 2016 Alexis Trouve
//

#ifndef CPP_INDIE_STUDIO_HEALSPELL_HH
# define CPP_INDIE_STUDIO_HEALSPELL_HH

#include <string>
#include "World.hh"
#include "ASpell.hh"

namespace gauntlet
{
  class HealAttack : public ASpell
    {
    protected:
      long		heal;
      double		range;
      double		radiusExplode;
    public:
      HealAttack(long heal, double nrange, double nradiusExplode,
		 int nid, const std::string &nname, double ncastTime);
      ~HealAttack();
      virtual void	 apply(double orientation, world::World &world,
			       gauntlet::Actor &SpellCaster,
			       std::pair<double, double> coordPointed);
    };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
