//
// ContainerObject.hh for inie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 13:56:57 2016 Alexis Trouve
// Last update Mon May  9 14:09:05 2016 Alexis Trouve
//

#ifndef CONTAINEROBJ_HH_
# define CONTAINEROBJ_HH_

#include "ItemContainer.hh"
#include "GameObject.hh"

namespace gauntlet {
    class ContainerObject : public GameObject {
    private:
        ItemContainer myItems;
    public:
        ContainerObject();

        ~ContainerObject();
    };
};

#endif
