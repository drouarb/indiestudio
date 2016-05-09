//
// Stats.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 13:46:11 2016 Alexis Trouve
// Last update Mon May  9 13:47:52 2016 Alexis Trouve
//

#include "Stats.hh"

gauntlet::Stats::Stats()
{
  HP = 0;
  normalHP = 0;
}

gauntlet::Stats::~Stats()
{
}

void  gauntlet::Stats::operator+=(const Stats stats)
{
  this->normalHP += stats.normalHP;
  this->HP += stats.HP;
  this->normalSpeed += stats.normalSpeed;
  this->speed += stats.speed;
  this->attackModifier += stats.attackModifier;
}