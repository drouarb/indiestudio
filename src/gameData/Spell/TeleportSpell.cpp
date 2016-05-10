//
// TeleportSpell.cpp for TeleportSpell in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 13:36:12 2016 Alexis Trouve
// Last update Tue May 10 17:30:19 2016 Alexis Trouve
//

#include "TeleportSpell.hh"

using namespace gauntlet;

TeleportSpell::TeleportSpell(bool nbump, long ndamage, short nangle,
			     short nnbrProj, double nrange, double nradiusExplode,
			     int nid, const std::string &nname, double ncastTime)
  : DistAttack(nbump, ndamage, nangle, nnbrProj, nrange, nradiusExplode, nid, nname, ncastTime)
{
  nbrProj = 1;
}

TeleportSpell::~TeleportSpell()
{

}

void	TeleportSpell:: apply(double orientation, World &world,
		       gauntlet::Actor &SpellCaster,
		       std::pair<double, double> coordPointed)
{
  
}
