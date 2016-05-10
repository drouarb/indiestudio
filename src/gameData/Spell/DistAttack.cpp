//
// DistAttack.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 13:19:44 2016 Alexis Trouve
// Last update Tue May 10 13:35:20 2016 Alexis Trouve
//

#include "DistAttack.hh"

using namespace gauntlet;

DistAttack::DistAttack(bool nbump, long ndamage, short nangle,
		       short nnbrProj, double nrange, double nradiusExplode,
		       int nid, const std::string &nname, double ncastTime) : ASpell(nid, nname, ncastTime)
{
  bump = nbump;
  damage = ndamage;
  angle = nangle;
  nbrProj = nnbrProj;
  range = nrange;
  radiusExplode = nradiusExplode;
}

DistAttack::~DistAttack()
{

}

void		DistAttack::apply(double orientation, World &world,
				  gauntlet::Actor &SpellCaster,
				  std::pair<double, double> coordPointed)
{
  
}
