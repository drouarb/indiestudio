//
// MeleeAttack.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include/gameData/Spell
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 10:23:22 2016 Alexis Trouve
// Last update Tue May 10 13:50:59 2016 Alexis Trouve
//

#ifndef MELEEATTACK_HH_
# define MELEEATTACK_HH_

#include "ASpell.hh"

namespace gauntlet
{
  class	MeleeAttack : public ASpell
  {
  protected:
    bool	bump;
    long	damage;
    short	angle;
    double	rangeDegat;
    double	distDo;
  public:
    MeleeAttack(bool nbump, long ndamage, short nangle,
		double nrangeDegat, double ndistDo, int id,
		const std::string &name, double castTime);
    ~MeleeAttack();
    void	apply(double norientation, World &world, gauntlet::Actor &SpellCaster,
		      std::pair<double, double> coordPointed);
  };
};

#endif
