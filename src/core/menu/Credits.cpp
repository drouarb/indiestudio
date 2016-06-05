#include "Credits.hh"
#include "Core.hh"

gauntlet::core::Credits::Credits(Core &core, int idStart, Menu *parent) :
        Menu(core, idStart, parent)
{
    buttons.push_back(Control(BUTTON, "Next", NULL, PBOTTOMRIGHT,
                              idStart + buttons.size(), core.ogre));
}

gauntlet::core::Credits::~Credits()
{ }

void
gauntlet::core::Credits::draw()
{
    drawButtons();

    if (core.gameIsRunning() == false)
        core.ogre.stopSound(0);
    core.ogre.showBackground(core.ogre.credit_vec[0]);
    core.ogre.playSound(-1, CREDIT_SOUND, false);

    image = 0;
    sw.set();
}

void
gauntlet::core::Credits::undraw()
{
    core.ogre.stopSound(-1);
    if (core.gameIsRunning() == false)
        {
            core.ogre.playSound(0, (MENU_SOUND), true);
            core.ogre.showBackground(BACKGROUND_BASIC);
        }
    else
        {
            core.ogre.hideBackground();
        }

    undrawButtons();
}

void
gauntlet::core::Credits::doButton(int btnId, struct t_hitItem &item)
{
    doNext(btnId, item);
}

void
gauntlet::core::Credits::tick()
{
    if (sw.ellapsedMs() > MS_PER_CREDIT)
        {
            struct t_hitItem item;
            doNext(0, item);
        }
}

void gauntlet::core::Credits::doNext(int btnId, struct t_hitItem & item)
{
    (void) btnId;
    (void) item;

    image++;
    if (image < core.ogre.credit_vec.size())
        {
            core.ogre.showBackground(core.ogre.credit_vec[image]);
            sw.set();
        }
    else
        {
            setOpen(false);
        }
}


