#ifndef  CREDITS_HH_
# define CREDITS_HH_

# include "Stopwatch.hh"
# include "Menu.hh"

# define MS_PER_CREDIT 5415

namespace gauntlet
{
    namespace core
    {
        class Credits : public Menu
        {
        public:
            Credits(Core &, int idStart, Menu *parent);
            ~Credits();

            void draw();
            void undraw();
            void tick();

        protected:
            void doButton(int, struct t_hitItem &);
            void doNext(int, struct t_hitItem &);

            unsigned int image;
            Stopwatch sw;
        };
    };
};

#endif
