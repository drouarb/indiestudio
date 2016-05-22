//
// Created by greg on 18/05/16.
//

#include <iostream>
#include <cassert>
#include "world/PhysicCollideLayer.hh"

int main() {
    std::cout << "" << std::endl;
    gauntlet::world::PhysicCollideLayer physicCollideLayer(10, 10);

    assert(physicCollideLayer.isWall(0, 0) == false);

    physicCollideLayer.setWall(0, 0);

    assert(physicCollideLayer.isWall(0, 0) == true);

    physicCollideLayer.setWall(5, 5, 2, 2);
//
//    assert(physicCollideLayer.checkCoordSize(5, 5, 2, 2) == true);

//    physicCollideLayer.setWall(8, 8, 3, 3);
}
