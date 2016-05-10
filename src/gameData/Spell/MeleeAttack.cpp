//
// MeleeAttack.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 13:00:56 2016 Alexis Trouve
// Last update Tue May 10 13:32:59 2016 Alexis Trouve
//

#include "MeleeAttack.hh"

using namespace gauntlet;

MeleeAttack::MeleeAttack(bool nbump, long ndamage, short nangle,
			 double nrangeDegat, double ndistDo, int nid,
			 const std::string &nname, double ncastTime) : ASpell(nid, nname, ncastTime)
{
  bump = nbump;
  damage = ndamage;
  angle = nangle;
  rangeDegat = nrangeDegat;
  distDo = ndistDo;
}

MeleeAttack::~MeleeAttack()
{

}

void		MeleeAttack::apply(double orientation, World &world,
				   Actor &SpellCaster,
				   std::pair<double, double> coordPointed)
{

}
