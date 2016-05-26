#include "Hud.hh"
#include "Core.hh"

gauntlet::core::Hud::Hud(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(PROGRESSBAR, "Health", new int(100), PBOTTOM,
			    idStart + buttons.size(), core.ogre));
}

gauntlet::core::Hud::~Hud()
{ }

void
gauntlet::core::Hud::draw()
{
  drawButtons();
}

void
gauntlet::core::Hud::undraw()
{
  undrawButtons();
}

void
gauntlet::core::Hud::setStats(int stat)
{
  t_hitItem item;

  item.value = stat;
  item.data = "";
  item.type = PROGRESSBAR;
  buttons[0].update(item);
}

void
gauntlet::core::Hud::doButton(int btnId, struct t_hitItem & item)
{
  (void)btnId;
  (void)item;
}
