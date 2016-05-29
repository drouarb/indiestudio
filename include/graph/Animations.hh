//
// Created by greg on 28/05/16.
//

#pragma once

#include "JSON/JsonArr.hpp"
#include "JSON/JsonParser.hpp"
#include "AnimationsList.hh"
#include "OgreUI.hh"
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

    class Animation
    {
     protected:
      animationSource type;
      std::string name;
      bool loop;
     public:
      virtual ~Animation(){}
      virtual bool update(double elapsedTime) = 0;
      virtual void reset() = 0;
      virtual std::string const & getName() const = 0;
    };

    class JSON : public Animation
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
      JSON(const std::string &filename, const std::string &animationName, Ogre::AnimationState *, bool loop);
      virtual bool update(double elapsedTime) final;
      virtual std::string const & getName() const final;
      virtual void reset() final;
    };

    /*
     * \quote
     * <Type, <filename, animationName>>
     */
    static const std::map<animations::AnimationsListJson, std::pair<std::string, std::string>> jsonMap = 	{
	    {SKELETON_SORCERER_JSON_M_SKELETON_SWING_RIGHT , { "skeleton_sorcerer.json", "M_SKELETON_SWING_RIGHT" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_COMBAT_MODE_B , { "skeleton_sorcerer.json", "M_SKELETON_COMBAT_MODE_B" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_DUCK_BELOW_SWING , { "skeleton_sorcerer.json", "M_SKELETON_DUCK_BELOW_SWING" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAGIC_LIGHT_SPELL , { "skeleton_sorcerer.json", "M_SKELETON_MAGIC_LIGHT_SPELL" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAGIC_SHOT_STRIGHT , { "skeleton_sorcerer.json", "M_SKELETON_MAGIC_SHOT_STRIGHT" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_COMBAT_MODE_C , { "skeleton_sorcerer.json", "M_SKELETON_COMBAT_MODE_C" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_BUFF_SPELL_A , { "skeleton_sorcerer.json", "M_SKELETON_BUFF_SPELL_A" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_BUFF_SPELL_B , { "skeleton_sorcerer.json", "M_SKELETON_BUFF_SPELL_B" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_FIRE_BALL_SPELL , { "skeleton_sorcerer.json", "M_SKELETON_FIRE_BALL_SPELL" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_SPELL_CAST_A , { "skeleton_sorcerer.json", "M_SKELETON_SPELL_CAST_A" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAKING_POTION , { "skeleton_sorcerer.json", "M_SKELETON_MAKING_POTION" }},
	    {SKELETON_WARLORD_JSON_SKELETON_WARLORD , { "skeleton_warlord.json", "SKELETON_WARLORD" }},
	    {SKELETON_WARLORD_JSON_SKELETON_IDLE , { "skeleton_warlord.json", "SKELETON_IDLE" }},
	    {SKELETON_WARLORD_JSON_SKELETON_USE_OBJECT , { "skeleton_warlord.json", "SKELETON_USE_OBJECT" }},
	    {SKELETON_WARLORD_JSON_SKELETON_ANGER , { "skeleton_warlord.json", "SKELETON_ANGER" }},
	    {SKELETON_WARLORD_JSON_SKELETON_DRINKING , { "skeleton_warlord.json", "SKELETON_DRINKING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_HIT_FROM_BACK , { "skeleton_warlord.json", "SKELETON_HIT_FROM_BACK" }},
	    {SKELETON_WARLORD_JSON_SKELETON_HIT_FROM_FRONT , { "skeleton_warlord.json", "SKELETON_HIT_FROM_FRONT" }},
	    {SKELETON_WARLORD_JSON_SKELETON_LOOKING_AROUND , { "skeleton_warlord.json", "SKELETON_LOOKING_AROUND" }},
	    {SKELETON_WARLORD_JSON_SKELETON_POINTING_A , { "skeleton_warlord.json", "SKELETON_POINTING_A" }},
	    {SKELETON_WARLORD_JSON_SKELETON_SALUTE , { "skeleton_warlord.json", "SKELETON_SALUTE" }},
	    {SKELETON_WARLORD_JSON_SKELETON_TALKING , { "skeleton_warlord.json", "SKELETON_TALKING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_THINKING , { "skeleton_warlord.json", "SKELETON_THINKING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_TRACKING , { "skeleton_warlord.json", "SKELETON_TRACKING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_SIT_DOWN , { "skeleton_warlord.json", "SKELETON_SIT_DOWN" }},
	    {SKELETON_WARLORD_JSON_SKELETON_SITTING , { "skeleton_warlord.json", "SKELETON_SITTING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_CAME_UP , { "skeleton_warlord.json", "SKELETON_CAME_UP" }},
	    {SKELETON_WARLORD_JSON_SKELETON_GOING_ASLEEP , { "skeleton_warlord.json", "SKELETON_GOING_ASLEEP" }},
	    {SKELETON_WARLORD_JSON_SKELETON_SLEEPING , { "skeleton_warlord.json", "SKELETON_SLEEPING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_WAKING_UP , { "skeleton_warlord.json", "SKELETON_WAKING_UP" }},
	    {SKELETON_WARLORD_JSON_SKELETON_WALKING_BACK , { "skeleton_warlord.json", "SKELETON_WALKING_BACK" }},
	    {SKELETON_WARLORD_JSON_SKELETON_CLIMBING_LADDER , { "skeleton_warlord.json", "SKELETON_CLIMBING_LADDER" }},
	    {SKELETON_WARLORD_JSON_SKELETON_CROUCHING , { "skeleton_warlord.json", "SKELETON_CROUCHING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_FALLING_DOWN , { "skeleton_warlord.json", "SKELETON_FALLING_DOWN" }},
	    {SKELETON_WARLORD_JSON_SKELETON_MOVING_LEFT , { "skeleton_warlord.json", "SKELETON_MOVING_LEFT" }},
	    {SKELETON_WARLORD_JSON_SKELETON_MOVING_RIGHT , { "skeleton_warlord.json", "SKELETON_MOVING_RIGHT" }},
	    {SKELETON_WARLORD_JSON_SKELETON_SNEAKING , { "skeleton_warlord.json", "SKELETON_SNEAKING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_RUN , { "skeleton_warlord.json", "SKELETON_RUN" }},
	    {SKELETON_WARLORD_JSON_SKELETON_JUMP_RUNING , { "skeleton_warlord.json", "SKELETON_JUMP_RUNING" }},
	    {SKELETON_WARLORD_JSON_SKELETON_DYING_A , { "skeleton_warlord.json", "SKELETON_DYING_A" }},
	    {SKELETON_WARLORD_JSON_SKELETON_WALK , { "skeleton_warlord.json", "SKELETON_WALK" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_WITH_WEAPON_WALK , { "skeleton_warlord.json", "2H_SKELETON_WITH_WEAPON_WALK" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_CHARGING , { "skeleton_warlord.json", "2H_SKELETON_CHARGING" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_COMBAT_MODE , { "skeleton_warlord.json", "2H_SKELETON_COMBAT_MODE" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_DODGE_BACKWARDS , { "skeleton_warlord.json", "2H_SKELETON_DODGE_BACKWARDS" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_DODGE_TO_LEFT , { "skeleton_warlord.json", "2H_SKELETON_DODGE_TO_LEFT" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_DODGE_TO_RIGH , { "skeleton_warlord.json", "2H_SKELETON_DODGE_TO_RIGH" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_DUCK_BELOW_HIGH_SWING , { "skeleton_warlord.json", "2H_SKELETON_DUCK_BELOW_HIGH_SWING" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_PARRY_FROM_STRIGHT_DOWN , { "skeleton_warlord.json", "2H_SKELETON_PARRY_FROM_STRIGHT_DOWN" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_PARRY_LOW_FRONT , { "skeleton_warlord.json", "2H_SKELETON_PARRY_LOW_FRONT" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_PARRY_MID_LEFT , { "skeleton_warlord.json", "2H_SKELETON_PARRY_MID_LEFT" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SPECAL_ATTACK_A , { "skeleton_warlord.json", "2H_SKELETON_SPECAL_ATTACK_A" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SPECAL_ATTACK_B , { "skeleton_warlord.json", "2H_SKELETON_SPECAL_ATTACK_B" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SWING_MID_LEFT , { "skeleton_warlord.json", "2H_SKELETON_SWING_MID_LEFT" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SWING_MID_RIGHT , { "skeleton_warlord.json", "2H_SKELETON_SWING_MID_RIGHT" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SWORD_SWING_HIGH_STRAIGHT_DOWN , { "skeleton_warlord.json", "2H_SKELETON_SWORD_SWING_HIGH_STRAIGHT_DOWN" }},
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SWORD_THRUST_MID, { "skeleton_warlord.json", "2H_SKELETON_SWORD_THRUST_MID" }}
    };
  }
}
