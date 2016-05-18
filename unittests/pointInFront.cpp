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

  gauntlet::ABody me(true, 1, 1.5 * SIZE_CASE, 1.5 * SIZE_CASE, 5, 5, 100);
  std::cout << "POS: " << 1.5 * SIZE_CASE << std::endl;

  std::pair<double, double> point = ecl.pointInFront(me, 100);
  std::cout << point.first << " " << point.second << std::endl;
}
