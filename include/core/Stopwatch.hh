//
// Timer.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:05:33 2016 Esteban Lewis
// Last update Mon May  9 18:00:00 2016 Esteban Lewis
//

#ifndef  STOPWATCH_HPP_
# define STOPWATCH_HPP_

# include <sys/time.h>
# include <time.h>

namespace			gauntlet
{
  namespace			core
  {
    class			Stopwatch
    {
    public:
      Stopwatch();
      ~Stopwatch();
      
      void			Set();
      long			EllapsedMs();
      
    private:
      struct timeval		startTime;
    };
  };
};

#endif
