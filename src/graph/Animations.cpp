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
  if (currentTimePosition > this->end)
    {
      std::cerr << "loop" << std::endl;
      if (loop)
	{
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
  std::cerr << "Création d'une animation" << std::endl;
  this->jsonObj = new ::JSON::JsonObj();
  this->jsonObj->ParseFrom(this->readJson(filename));
  this->type = animationSource::JSON;
  this->loop = loop;
  findProprerties(animationName);
  this->currentTimePosition = this->begin;
  std::cout << "Animation " << this->getName() << " construite, begin: " <<
  this->begin << ", end:" << this->end << std::endl;
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
    {
      std::cerr << "ICIIIIIIIIIIIIIII" << std::endl;
    }
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

std::string animations::JSONAnimation::readJson(const std::string &filename)
{
  std::string line;
  std::string dest;
  std::ifstream file("./json/" + filename);

  std::cout << "fichier: " << "./json/" + filename << std::endl;

  if (!file.is_open())
    {
      return "";
    }

  while (getline(file, line))
    {
      dest += line;
    }

//    std::cerr << "RES: " << dest << std::endl;

  return dest;
}

animations::JSONAnimation::~JSONAnimation()
{
  std::cerr << "JSONAnimation destructor" << std::endl;
}



