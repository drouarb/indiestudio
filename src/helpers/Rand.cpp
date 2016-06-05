#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include "Rand.hh"

int
Rand::generate()
{
  static bool sranded = false;

  if (!sranded)
    {
#ifdef _WIN32
		srand(GetTickCount());
#else
	  struct timeval time;
      gettimeofday(&time, NULL);
      srand(getpid() + time.tv_usec);
#endif
      sranded = true;
    }
  return (rand());
}
