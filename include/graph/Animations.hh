//
// Created by greg on 28/05/16.
//

#ifndef GAUNTLET_ANIMATIONS_HH
#define GAUNTLET_ANIMATIONS_HH


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
      TRACK,
      NAME
    };

    class animation
    {
     protected:
      animationSource type;
     public:
      virtual void update(float elapsedTime) = 0;
    };

    class JSON : public animation
    {
     private:
      ::JSON::JsonObj jsonObj;
      const std::string & filename;
     public:
      JSON(const std::string &filename);
      virtual void update(float elapsedTime) final;
    };

  }
}

#endif //GAUNTLET_ANIMATIONS_HH
