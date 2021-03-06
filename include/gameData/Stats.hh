//
// Stats.hh for Stats in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 11:29:29 2016 Alexis Trouve
// Last update Sat Jun  4 15:03:04 2016 Alexis Trouve
//

#ifndef STATS_HH_
# define STATS_HH_

namespace gauntlet {
  class Stats {
  public:
    long HP;
    long normalHP;
    double speed;
    double normalSpeed;
    double attackModifier;
  public:
    Stats();
    ~Stats();
    
    void operator+=(const Stats stats);
    void operator=(const Stats stats);
  };
};

#endif
