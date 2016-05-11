//
// ContainerObject.hh for inie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 13:56:57 2016 Alexis Trouve
// Last update Tue May 10 20:35:59 2016 Alexis Trouve
//

#ifndef CONTAINEROBJ_HH_
# define CONTAINEROBJ_HH_

#include "ItemContainer.hh"

namespace gauntlet
{
  class ContainerObject
  {
  private:
    ItemContainer items;
  public:
    ContainerObject();
    
    ~ContainerObject();
  };
};

#endif
