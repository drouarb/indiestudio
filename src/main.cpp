//
// Created by drouar_b on 02/05/16.
//

#include <iostream>
#include <helpers/StackTrace.h>
#include "Core.hh"
#include "GameServer.hh"

int main(int ac, char **av)
{
  StackTrace::init();
  if (ac == 1)
    gauntlet::core::Core();
  else if (ac == 3)
    gauntlet::world::GameServer(av[1], atoi(av[2]));
  else
    std::cout << "USAGE" << std::endl
    << "Game:" << std::endl << "\t" << av[0] << std::endl
    << "Server:" << std::endl << "\t" << av[0] << " [map] [port]" << std::endl;
  return (0);
}
