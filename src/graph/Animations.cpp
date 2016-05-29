//
// Created by greg on 28/05/16.
//

#include <OGRE/Ogre.h>
#include "Animations.hh"

using namespace gauntlet;

//std::map<animations::AnimationsListJson, std::pair<std::string, std::string>> gauntlet::animations::jsonMap =
//;


bool animations::JSONAnimation::update(double elapsedTime)
{
  this->currentTimePosition += elapsedTime;
  if (currentTimePosition > (this->end - this->begin))
    {
      if (loop)
	{
	  return false;
	}
      currentTimePosition =
	      this->begin + (currentTimePosition - (this->end - this->begin));
    }
  this->animationState->setTimePosition(
	  static_cast<float>(currentTimePosition));
  return true;
}

animations::JSONAnimation::JSONAnimation(const std::string &filename,
					 const std::string &animationName,
					 Ogre::AnimationState *animationState,
					 bool loop) : filename(
	filename), animationState(animationState)
{
  this->jsonObj.ParseFrom(filename);
  this->type = animationSource::JSON;
  this->loop = loop;

  findProprerties(animationName);
}

void gauntlet::animations::JSONAnimation::findProprerties(
	const std::string &animationName)
{
  std::string an = animationName;
  std::transform(an.begin(), an.end(), an.begin(), ::toupper);
  ::JSON::JsonArr &
	  arr = dynamic_cast<::JSON::JsonArr &>(this->jsonObj.GetObj(
		  "Animation"));
  for (size_t i = 0; i < arr.Size(); ++i)
    {
      ::JSON::JsonObj &json = dynamic_cast<::JSON::JsonObj &>(arr[i]);
      std::string name = dynamic_cast<::JSON::JsonStr &>(json.GetObj(
	      "name")).Get();
      std::transform(name.begin(), name.end(), name.begin(), ::toupper);
      if (an == name)
      {
	this->name = name;
	try
	  {
	    this->begin = stod(
		    dynamic_cast<::JSON::JsonStr &>(json.GetObj(
			    "begin")).Get());
	    this->end = stod(
		    dynamic_cast<::JSON::JsonStr &>(json.GetObj(
			    "end")).Get());
	  } catch (std::invalid_argument)
	  {
	    throw std::runtime_error("Invalid number");
	  }
	this->currentTimePosition = 0;
	return;
      }
    }
  throw std::logic_error("Cannot find " + animationName);
}

std::string const &animations::JSONAnimation::getName() const
{
  return this->name;
}

void animations::JSONAnimation::reset()
{
  this->animationState->setTimePosition(0);
}