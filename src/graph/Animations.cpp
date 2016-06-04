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
  this->currentTimePosition += elapsedTime * this->speed;
  if (currentTimePosition > this->end)
    {
      if (!loop)
	{
	  //TODO test this
	  if (this->animationState->getAnimationName() != "death")
	    this->animationState->setTimePosition(static_cast<float>(0));
	  return false;
	}
      this->currentTimePosition = this->begin;
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
  std::cout << "--------------------------> animationName: " << animationName << std::endl;
  this->jsonObj = new ::JSON::JsonObj();
  this->jsonObj->ParseFrom(this->readJson(filename));
  this->type = animationSource::JSON;
  this->loop = loop;
  findProprerties(animationName);
  this->currentTimePosition = this->begin;
}

void gauntlet::animations::JSONAnimation::findProprerties(
	const std::string &animationName)
{
  std::string an = animationName;
  std::transform(an.begin(), an.end(), an.begin(), ::toupper);
  ::JSON::JsonArr arr;
  try
    {
      arr = dynamic_cast<::JSON::JsonArr &>(this->jsonObj->GetObj(
	      "animation"));
    } catch (...)
    { }
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
	      try
		{
		  this->speed = stod(
			  dynamic_cast<::JSON::JsonStr &>(json.GetObj(
				  "speed")).Get());
		} catch (...) //Speed is not mandatory
		{ }
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

std::string animations::JSONAnimation::readJson(const std::string &filename)
{
  std::string line;
  std::string dest;
  std::ifstream file("./json/" + filename);

  if (!file.is_open())
    {
      return "";
    }

  while (getline(file, line))
    {
      dest += line;
    }
  return dest;
}

animations::JSONAnimation::~JSONAnimation()
{ }

std::ostream &animations::operator<<(std::ostream &stream,
				     animations::AnimationsListJson const &animation)
{
  try
    {
      std::pair<std::string, std::string> pair = jsonMap.at(animation);
      stream << "file: " << pair.first << ", name: " << pair.second << std::endl;
    } catch (std::exception &e)
    {
      stream << "id: " << static_cast<int>(animation) << e.what() << std::endl;
    }
  return (stream);
}