#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "Rand.hh"

int
Rand::generate()
{
  static bool sranded = false;

  if (!sranded)
    {
      struct timeval time;
      gettimeofday(&time, NULL);
      srand(getpid() + time.tv_usec);
      sranded = true;
    }
  return (rand());
}
