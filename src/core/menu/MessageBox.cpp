#include "MessageBox.hh"
#include "Core.hh"

gauntlet::core::MessageBox::MessageBox(Core & core, int idStart, Menu * parent, std::string const & msg) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(LABEL, "", NULL, PCENTER, idStart + buttons.size(),
			     core.ogre));
  buttons.push_back(Control(BUTTON, "  Ok  ", NULL, PCENTER, idStart + buttons.size(),
			    core.ogre));
  setMsg(msg);
}

gauntlet::core::MessageBox::~MessageBox()
{ }

void
gauntlet::core::MessageBox::draw()
{
  drawButtons();
}

void
gauntlet::core::MessageBox::undraw()
{
  undrawButtons();
}

void
gauntlet::core::MessageBox::setMsg(std::string const & newmsg)
{
  buttons[0].setStr(newmsg);
}

void
gauntlet::core::MessageBox::doButton(int btnId, struct t_hitItem & item)
{
  (void)btnId;
  (void)item;
  setOpen(false);
}
