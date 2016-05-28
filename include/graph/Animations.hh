//
// Created by greg on 28/05/16.
//

#ifndef GAUNTLET_ANIMATIONS_HH
#define GAUNTLET_ANIMATIONS_HH


#include "JSON/JsonArr.hpp"
#include "JSON/JsonParser.hpp"
#include <string>
#include <helpers/JSON/JsonObj.hpp>

namespace gauntlet
{
  namespace animations
  {
    enum animationSource
    {
      JSON,
      NAME
    };

    class animation
    {
     protected:
      animationSource type;
      std::string name;
     public:
      virtual void update(double elapsedTime) = 0;
      virtual std::string const & getName() const = 0;
    };

    class JSON : public animation
    {
     private:
      ::JSON::JsonObj jsonObj;
      const std::string & filename;
      Ogre::AnimationState *animationState;
      double begin = -1;
      double end = -1;
      double currentTimePosition = 0;

     private:
      void findProprerties(const std::string &animationName);

     public:
      JSON(const std::string &filename, const std::string &animationName, Ogre::AnimationState *);
      virtual void update(double elapsedTime) final;
      virtual std::string const & getName() const final;
    };

  }
}

#endif //GAUNTLET_ANIMATIONS_HH
