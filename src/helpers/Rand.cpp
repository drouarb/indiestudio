#include "Rand.hh"
#include <stdlib.h>

int
Rand::generate()
{
  static bool sranded = false;

  if (!sranded)
    {
      
      sranded = true;
    }
  return (rand());
}
