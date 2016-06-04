#ifndef  LOADMENU_HH_
# define LOADMENU_HH_

# define SAVE_DIR "./map/"
# define NEW_SAVE "NEW_MAP"

# include <map>
# include "Menu.hh"
# include "Core.hh"

namespace gauntlet
{
    namespace core
    {
        class LoadMenu : public Menu
        {
        public:
            LoadMenu(Core &, int idStart, Menu *parent);
            ~LoadMenu();

            void draw();
            void undraw();

        protected:
            std::map<int, void (LoadMenu::*)(struct t_hitItem &)> funs;
            std::vector<std::string> saves;
            std::string selected;

            void getSaves();
            void message(std::string const &);
            void doButton(int, struct t_hitItem &);
            void doSelect(struct t_hitItem &);
            void doLoad(struct t_hitItem &);
            void doReturn(struct t_hitItem &);
        };
    };
};

#endif
