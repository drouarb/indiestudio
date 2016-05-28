//
// Created by greg on 28/05/16.
//

#include <OGRE/Ogre.h>
#include "Animations.hh"

using namespace gauntlet;

void animations::JSON::update(double elapsedTime)
{
  this->currentTimePosition += elapsedTime;
  if (currentTimePosition > (this->end - this->begin))
    {
      currentTimePosition =
	      this->begin + (currentTimePosition - (this->end - this->begin));
    }
  this->animationState->setTimePosition(
	  static_cast<float>(currentTimePosition));
}

animations::JSON::JSON(const std::string &filename,
		       const std::string &animationName,
		       Ogre::AnimationState *animationState) : filename(
	filename), animationState(animationState)
{
  this->jsonObj.ParseFrom(filename);
  this->type = animationSource::JSON;

  findProprerties(animationName);
}

void gauntlet::animations::JSON::findProprerties(
	const std::string &animationName)
{
  ::JSON::JsonArr &arr = dynamic_cast<::JSON::JsonArr &>(this->jsonObj.GetObj(
	  "animation"));
  for (size_t i = 0; i < arr.Size(); ++i)
    {
      ::JSON::JsonObj &json = dynamic_cast<::JSON::JsonObj &>(arr[i]);
      const std::string &name = dynamic_cast<::JSON::JsonStr &>(json.GetObj(
	      "name")).Get();
      if (name == animationName)
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

std::string const &animations::JSON::getName() const
{
  return this->name;
}