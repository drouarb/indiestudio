//
// Item.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 11:24:05 2016 Alexis Trouve
// Last update Mon May  9 15:02:36 2016 Alexis Trouve
//

#ifndef ITEM_HH_
# define ITEM_HH_

#include "Stats.hh"

class	Item
{
private:
  int		id;
  int		number;
  int		price;
  Stats		mystat;
public:
  Item();
  ~Item();
};

#endif
