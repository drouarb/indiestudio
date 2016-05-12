//
// GameObject.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 17:13:51 2016 Alexis Trouve
// Last update Thu May 12 17:14:29 2016 Alexis Trouve
//

#include "GameObject.hh"

using namespace gauntlet;

GameObject::GameObject(bool ncollide, int nid, double posx, double posy,
             double sizex, double sizey, short norient)
  : ABody(ncollide, nid, posx, posy, sizex, sizey, norient)
{
}

GameObject::GameObject(int nid, double posx, double posy,
             double sizex, double sizey, short norient)
  : ABody(nid, posx, posy, sizex, sizey, norient)
{
}

GameObject::~GameObject()
{
}
