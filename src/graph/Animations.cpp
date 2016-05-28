//
// Created by greg on 28/05/16.
//

#include "Animations.hh"

using namespace gauntlet;
using namespace animations;

void animations::JSON::update(float elapsedTime)
{

}


animations::JSON::JSON(const std::string &filename) : filename(filename)
{
  this->jsonObj.ParseFrom(filename);
  this->type = animationSource::JSON;
}

