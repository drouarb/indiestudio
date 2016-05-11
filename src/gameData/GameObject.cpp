//
// GameObject.cpp for GameObject in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:07:25 2016 Alexis Trouve
// Last update Tue May 10 21:02:54 2016 Alexis Trouve
//

#include "GameObject.hh"

using namespace gauntlet;

GameObject::GameObject(bool collide, int nid, double posx,
		       double posy, double sizex, double sizey, short norient)
  : ABody(collide, nid, posx, posy, sizex, sizey, norient)
{

}

GameObject::GameObject(int nid, double posx, double posy,
		       double sizex, double sizey, short norient)
  : ABody(true, nid, posx, posy, sizex, sizey, norient)
{

}

GameObject::~GameObject()
{

}
