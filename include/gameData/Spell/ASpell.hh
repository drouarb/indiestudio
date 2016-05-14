//
// ASpell.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 11:05:51 2016 Alexis Trouve
// Last update Sat May 14 15:31:11 2016 Alexis Trouve
//

#ifndef CPP_INDIE_STUDIO_ASPELL_HH
# define CPP_INDIE_STUDIO_ASPELL_HH

#include <string>
#include "World.hh"
#include "Actor.hh"

namespace gauntlet
{
  namespace world
  {
    class World;
  };

  class Actor;
  
  class ASpell
  {
  protected:
    int id;
    std::string	name;
    double castTime;
  public:
    ASpell(int nid, std::string nname, double ncastTime);
    virtual ~ASpell();
    virtual void	 apply(double orientation, world::World &world,
			       gauntlet::Actor *SpellCaster,
			       std::pair<double, double> coordPointed) = 0;
  };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
