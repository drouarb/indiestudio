//
// CoreUIObserver.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:56:08 2016 Esteban Lewis
// Last update Mon May 30 10:39:35 2016 Esteban Lewis
//

#include "CoreUIObserver.hh"
#include "Core.hh"

gauntlet::core::CoreUIObserver::CoreUIObserver(Core &core) : core(core)
{ }

gauntlet::core::CoreUIObserver::~CoreUIObserver()
{ }

void
gauntlet::core::CoreUIObserver::keyDown(Key key)
{
    core.keyDown(key);
}

void
gauntlet::core::CoreUIObserver::keyUp(Key key)
{
    core.keyUp(key);
}

void
gauntlet::core::CoreUIObserver::mouseMove(int x, int y)
{
    core.mouseMove(x, y);
}

void gauntlet::core::CoreUIObserver::itemClick(int buttonId, struct t_hitItem &item)
{
    core.buttonClick(buttonId, item);
}

void gauntlet::core::CoreUIObserver::frameStarted()
{
    core.actionlists.doActions();
    core.tick();
}
