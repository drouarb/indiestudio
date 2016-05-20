//
// Created by drouar_b on 02/05/16.
//

#include <iostream>
#include "Core.hh"
#include "World.hh"
#include "Math.hh"

int main()
{
  std::cout << "Hello maggle" << std::endl;
  //gauntlet::core::Core();
  gauntlet::world::Math::init();
  gauntlet::world::PhysicCollideLayer pcl(3 * SIZE_CASE, 3 * SIZE_CASE);
  gauntlet::world::EntityCollideLayer ecl(&pcl);

  ecl.map[0][0].Entity.push_back(new gauntlet::ABody(true, 1, 0, 0, 50, 50, 0));
  ecl.map[0][0].Entity.push_back(new gauntlet::ABody(true, 2, 350, 5, 50, 50, 0));
  ecl.map[1][1].Entity.push_back(new gauntlet::ABody(true, 3, 450, 450, 50, 50, 0));
  ecl.map[2][2].Entity.push_back(new gauntlet::ABody(true, 4, 850, 850, 50, 50, 0));
  ecl.map[2][2].Entity.push_back(new gauntlet::ABody(true, 5, 1100, 1100, 5, 5, 0));

  std::list<gauntlet::ABody*> res = ecl.giveBodyInAreaCone(1200, 1200, 234, 10000, 0);
  for (std::list<gauntlet::ABody*>::iterator it = res.begin(); it != res.end(); ++it)
    std::cout << (*it)->getId() << std::endl;
}
