//
// HealAttack.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 13:29:21 2016 Alexis Trouve
// Last update Sat May 14 15:32:18 2016 Alexis Trouve
//

#include "HealAttack.hh"

using namespace gauntlet;

HealAttack::HealAttack(long nheal, double nrange, double nradiusExplode,
		       int nid, const std::string &nname, double ncastTime) : ASpell(nid, nname, ncastTime)
{
  heal = nheal;
  range = nrange;
  radiusExplode = nradiusExplode;
}

HealAttack::~HealAttack()
{

}

void	HealAttack::apply(double orientation, world::World &world,
			  Actor *SpellCaster, std::pair<double, double> coordPointed)
{

}
