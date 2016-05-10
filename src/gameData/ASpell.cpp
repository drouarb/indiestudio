//
// Created by jonas_e on 5/9/16.
//

#include "ASpell.hh"

using namespace gauntlet;

ASpell::ASpell(int nid, std::string nname, double ncastTime)
{
  id = nid;
  name = nname;
  castTime = ncastTime;
}

ASpell::~ASpell()
{

}
