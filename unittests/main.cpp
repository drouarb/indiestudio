//
// Created by drouard_b on 02/05/16.
//

#include <iostream>
#include "Core.hh"
#include "World.hh"

int main()
{
  std::cout << "Hello maggle" << std::endl;
  //gauntlet::core::Core();
  gauntlet::world::PhysicCollideLayer pcl;
  gauntlet::world::EntityCollideLayer ecl(&pcl);
  ecl.sizeX = 3;
  ecl.sizeY = 3;
  ecl.map = new gauntlet::world::t_ca_line[3];
  for (int i = 0; i < 3; ++i)
    ecl.map[i] = new gauntlet::world::CollidingArea[3];

  ecl.map[0][0].Entity.push_back(new gauntlet::ABody(true, 1, 0, 0, 5, 5, 0));
  ecl.map[0][0].Entity.push_back(new gauntlet::ABody(true, 2, 350, 350, 5, 5, 0));
  ecl.map[1][1].Entity.push_back(new gauntlet::ABody(true, 3, 450, 450, 5, 5, 0));
  ecl.map[2][2].Entity.push_back(new gauntlet::ABody(true, 4, 850, 850, 5, 5, 0));
  ecl.map[2][2].Entity.push_back(new gauntlet::ABody(true, 5, 1100, 1100, 5, 5, 0));

  std::list<gauntlet::ABody*> res = ecl.giveBodyInAreaCone(1200, 0, 400, 2000, 78);
  for (std::list<gauntlet::ABody*>::iterator it = res.begin(); it != res.end(); ++it)
    std::cout << (*it)->getId() << std::endl;
}
