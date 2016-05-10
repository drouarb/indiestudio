//
// DistAttack.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 11:05:51 2016 Alexis Trouve
// Last update Tue May 10 16:58:47 2016 Alexis Trouve
//

#ifndef CPP_INDIE_STUDIO_DISTSPELL_HH
# define CPP_INDIE_STUDIO_DISTSPELL_HH

#include <string>
#include "World.hh"
#include "ASpell.hh"

namespace gauntlet
{
  class DistAttack : public ASpell
    {
    protected:
      bool	bump;
      long	damage;
      short	angle;
      short	nbrProj;
      double	range;
      double	radiusExplode;
    public:
      DistAttack(bool nbump, long ndamage, short nangle,
		 short nnbrProj, double nrange, double nradiusExplode,
		 int nid, const std::string &nname, double ncastTime);
      virtual ~DistAttack();
      virtual void	 apply(double orientation, World &world,
			       gauntlet::Actor &SpellCaster,
			       std::pair<double, double> coordPointed);
    };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
