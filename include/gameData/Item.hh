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

#include <string>
#include "Stats.hh"

namespace gauntlet {
    class Item {
    private:
        //bool equiped;
        bool consumable;
        int id;
        std::string name;
        int number;
        int price;
        bool key;
        bool upgrade;
        Stats stats;
    public:
        Item();
        ~Item();

        Stats   getStats();
        bool    isConsumable();
        bool    isKey();
        void    setKey(bool key);
        bool    operator==(Item item);
        bool    operator<(Item item);
        int     getNewId();
        void    generateItem(int pf);
        bool    isUpgrade();
        void    setPrice(int price);
        void    setId();
        static bool compare(Item item, Item item2);
        std::string getName();
        void setAsConsummable();
        Stats *modifyStats();
    };
};

#endif
