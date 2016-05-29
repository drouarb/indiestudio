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

    class JSONAnimation : public Animation
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
      JSONAnimation(const std::string &filename, const std::string &animationName, Ogre::AnimationState *, bool loop);
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
	    {SKELETON_WARLORD_JSON_2H_SKELETON_SWORD_THRUST_MID, { "skeleton_warlord.json", "2H_SKELETON_SWORD_THRUST_MID" }},
	    {SKELETON_SORCERER_JSON_SKELETON_IDLE, { "skeleton_sorcerer.json", "Skeleton_Idle" }},
	    {SKELETON_SORCERER_JSON_SKELETON_USE_OBJECT, { "skeleton_sorcerer.json", "Skeleton_Use_object" }},
	    {SKELETON_SORCERER_JSON_SKELETON_ANGER, { "skeleton_sorcerer.json", "Skeleton_anger" }},
	    {SKELETON_SORCERER_JSON_SKELETON_DRINKING, { "skeleton_sorcerer.json", "Skeleton_Drinking" }},
	    {SKELETON_SORCERER_JSON_SKELETON_HIT_FROM_BACK, { "skeleton_sorcerer.json", "Skeleton_Hit_from_back" }},
	    {SKELETON_SORCERER_JSON_SKELETON_HIT_FROM_FRONT, { "skeleton_sorcerer.json", "Skeleton_Hit_from_front" }},
	    {SKELETON_SORCERER_JSON_SKELETON_LOOKING_AROUND, { "skeleton_sorcerer.json", "Skeleton_Looking_around" }},
	    {SKELETON_SORCERER_JSON_SKELETON_POINTING_A, { "skeleton_sorcerer.json", "Skeleton_pointing_A" }},
	    {SKELETON_SORCERER_JSON_SKELETON_SALUTE, { "skeleton_sorcerer.json", "Skeleton_salute" }},
	    {SKELETON_SORCERER_JSON_SKELETON_TALKING, { "skeleton_sorcerer.json", "Skeleton_Talking" }},
	    {SKELETON_SORCERER_JSON_SKELETON_THINKING, { "skeleton_sorcerer.json", "Skeleton_thinking" }},
	    {SKELETON_SORCERER_JSON_SKELETON_TRACKING, { "skeleton_sorcerer.json", "Skeleton_Tracking" }},
	    {SKELETON_SORCERER_JSON_SKELETON_SIT_DOWN, { "skeleton_sorcerer.json", "Skeleton_sit_down" }},
	    {SKELETON_SORCERER_JSON_SKELETON_SITTING, { "skeleton_sorcerer.json", "Skeleton_sitting" }},
	    {SKELETON_SORCERER_JSON_SKELETON_CAME_UP, { "skeleton_sorcerer.json", "Skeleton_came_up" }},
	    {SKELETON_SORCERER_JSON_SKELETON_GOING_ASLEEP, { "skeleton_sorcerer.json", "Skeleton_Going_asleep" }},
	    {SKELETON_SORCERER_JSON_SKELETON_SLEEPING, { "skeleton_sorcerer.json", "Skeleton_sleeping" }},
	    {SKELETON_SORCERER_JSON_SKELETON_WAKING_UP, { "skeleton_sorcerer.json", "Skeleton_waking_up" }},
	    {SKELETON_SORCERER_JSON_SKELETON_WALKING_BACK, { "skeleton_sorcerer.json", "Skeleton_walking_back" }},
	    {SKELETON_SORCERER_JSON_SKELETON_CLIMBING_LADDER, { "skeleton_sorcerer.json", "Skeleton_Climbing_ladder" }},
	    {SKELETON_SORCERER_JSON_SKELETON_CROUCHING, { "skeleton_sorcerer.json", "Skeleton_Crouching" }},
	    {SKELETON_SORCERER_JSON_SKELETON_FALLING_DOWN, { "skeleton_sorcerer.json", "Skeleton_falling_down" }},
	    {SKELETON_SORCERER_JSON_SKELETON_MOVING_LEFT, { "skeleton_sorcerer.json", "Skeleton_Moving_left" }},
	    {SKELETON_SORCERER_JSON_SKELETON_MOVING_RIGHT, { "skeleton_sorcerer.json", "Skeleton_Moving_right" }},
	    {SKELETON_SORCERER_JSON_SKELETON_SNEAKING, { "skeleton_sorcerer.json", "Skeleton_Sneaking" }},
	    {SKELETON_SORCERER_JSON_SKELETON_RUN, { "skeleton_sorcerer.json", "Skeleton_Run" }},
	    {SKELETON_SORCERER_JSON_SKELETON_JUMP_RUNING, { "skeleton_sorcerer.json", "Skeleton_Jump_runing" }},
	    {SKELETON_SORCERER_JSON_SKELETON_DYING_A, { "skeleton_sorcerer.json", "Skeleton_Dying_A" }},
	    {SKELETON_SORCERER_JSON_SKELETON_WALK, { "skeleton_sorcerer.json", "Skeleton_walk" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_COMBAT_MODE_A, { "skeleton_sorcerer.json", "M_skeleton_combat_mode_A" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_DODGE_TO_LEFT, { "skeleton_sorcerer.json", "M_skeleton_dodge_to_left" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_DODGE_TO_RIGHT, { "skeleton_sorcerer.json", "M_skeleton_dodge_to_right" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_STAF_BLOCK, { "skeleton_sorcerer.json", "M_skeleton_staf_block" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_STAFF_EARTHQUAKE_SPELL, { "skeleton_sorcerer.json", "M_skeleton_staff_earthquake_spell" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_STAFF_HIT, { "skeleton_sorcerer.json", "M_skeleton_staff_Hit" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_STRAIGHT_DOWN_HIT, { "skeleton_sorcerer.json", "M_skeleton_straight_down_hit" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_SWING_RIGHT, { "skeleton_sorcerer.json", "M_skeleton_swing_right" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_COMBAT_MODE_B, { "skeleton_sorcerer.json", "M_skeleton_combat_mode_B" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_DUCK_BELOW_SWING, { "skeleton_sorcerer.json", "M_skeleton_duck_below_swing" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAGIC_LIGHT_SPELL, { "skeleton_sorcerer.json", "M_skeleton_magic_light_spell" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAGIC_SHOT_STRIGHT, { "skeleton_sorcerer.json", "M_skeleton_magic_shot_stright" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_COMBAT_MODE_C, { "skeleton_sorcerer.json", "M_skeleton_combat_mode_C" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_BUFF_SPELL_A, { "skeleton_sorcerer.json", "M_skeleton_buff_spell_A" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_BUFF_SPELL_B, { "skeleton_sorcerer.json", "M_skeleton_buff_spell_B" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_FIRE_BALL_SPELL, { "skeleton_sorcerer.json", "M_skeleton_fire_ball_spell" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_SPELL_CAST_A, { "skeleton_sorcerer.json", "M_skeleton_spell_cast_A" }},
	    {SKELETON_SORCERER_JSON_M_SKELETON_MAKING_POTION, { "skeleton_sorcerer.json", "M_skeleton_making_potion" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_IDLE, { "skeleton_archier.json", "Skeleton_Idle" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_USE_OBJECT, { "skeleton_archier.json", "Skeleton_Use_object" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_ANGER, { "skeleton_archier.json", "Skeleton_anger" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_DRINKING, { "skeleton_archier.json", "Skeleton_Drinking" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_HIT_FROM_BACK, { "skeleton_archier.json", "Skeleton_Hit_from_back" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_HIT_FROM_FRONT, { "skeleton_archier.json", "Skeleton_Hit_from_front" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_LOOKING_AROUND, { "skeleton_archier.json", "Skeleton_Looking_around" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_POINTING_A, { "skeleton_archier.json", "Skeleton_pointing_A" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_SALUTE, { "skeleton_archier.json", "Skeleton_salute" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_TALKING, { "skeleton_archier.json", "Skeleton_Talking" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_THINKING, { "skeleton_archier.json", "Skeleton_thinking" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_TRACKING, { "skeleton_archier.json", "Skeleton_Tracking" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_SIT_DOWN, { "skeleton_archier.json", "Skeleton_sit_down" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_SITTING, { "skeleton_archier.json", "Skeleton_sitting" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_CAME_UP, { "skeleton_archier.json", "Skeleton_came_up" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_GOING_ASLEEP, { "skeleton_archier.json", "Skeleton_Going_asleep" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_SLEEPING, { "skeleton_archier.json", "Skeleton_sleeping" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_WAKING_UP, { "skeleton_archier.json", "Skeleton_waking_up" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_WALKING_BACK, { "skeleton_archier.json", "Skeleton_walking_back" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_CLIMBING_LADDER, { "skeleton_archier.json", "Skeleton_Climbing_ladder" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_CROUCHING, { "skeleton_archier.json", "Skeleton_Crouching" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_FALLING_DOWN, { "skeleton_archier.json", "Skeleton_falling_down" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_MOVING_LEFT, { "skeleton_archier.json", "Skeleton_Moving_left" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_MOVING_RIGHT, { "skeleton_archier.json", "Skeleton_Moving_right" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_SNEAKING, { "skeleton_archier.json", "Skeleton_Sneaking" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_RUN, { "skeleton_archier.json", "Skeleton_Run" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_JUMP_RUNING, { "skeleton_archier.json", "Skeleton_Jump_runing" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_DYING_B, { "skeleton_archier.json", "Skeleton_Dying_A" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_1H_WALK, { "skeleton_archier.json", "Skeleton_walk" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_1H_DODGE_TO_LEFT, { "skeleton_archier.json", "M_skeleton_dodge_to_left" }},
	    {SKELETON_ARCHIER_JSON_SKELETON_1H_DODGE_TO_RIGHT, { "skeleton_archier.json", "M_skeleton_dodge_to_right" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_IDLE, { "skeleton_footman.json", "Skeleton_Idle" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_USE_OBJECT, { "skeleton_footman.json", "Skeleton_Use_object" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_ANGER, { "skeleton_footman.json", "Skeleton_anger" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_DRINKING, { "skeleton_footman.json", "Skeleton_Drinking" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_HIT_FROM_BACK, { "skeleton_footman.json", "Skeleton_Hit_from_back" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_HIT_FROM_FRONT, { "skeleton_footman.json", "Skeleton_Hit_from_front" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_LOOKING_AROUND, { "skeleton_footman.json", "Skeleton_Looking_around" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_POINTING_A, { "skeleton_footman.json", "Skeleton_pointing_A" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_SALUTE, { "skeleton_footman.json", "Skeleton_salute" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_TALKING, { "skeleton_footman.json", "Skeleton_Talking" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_THINKING, { "skeleton_footman.json", "Skeleton_thinking" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_TRACKING, { "skeleton_footman.json", "Skeleton_Tracking" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_SIT_DOWN, { "skeleton_footman.json", "Skeleton_sit_down" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_SITTING, { "skeleton_footman.json", "Skeleton_sitting" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_CAME_UP, { "skeleton_footman.json", "Skeleton_came_up" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_GOING_ASLEEP, { "skeleton_footman.json", "Skeleton_Going_asleep" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_SLEEPING, { "skeleton_footman.json", "Skeleton_sleeping" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_WAKING_UP, { "skeleton_footman.json", "Skeleton_waking_up" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_WALKING_BACK, { "skeleton_footman.json", "Skeleton_walking_back" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_CLIMBING_LADDER, { "skeleton_footman.json", "Skeleton_Climbing_ladder" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_CROUCHING, { "skeleton_footman.json", "Skeleton_Crouching" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_FALLING_DOWN, { "skeleton_footman.json", "Skeleton_falling_down" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_MOVING_LEFT, { "skeleton_footman.json", "Skeleton_Moving_left" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_MOVING_RIGHT, { "skeleton_footman.json", "Skeleton_Moving_right" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_SNEAKING, { "skeleton_footman.json", "Skeleton_Sneaking" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_RUN, { "skeleton_footman.json", "Skeleton_Run" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_JUMP_RUNING, { "skeleton_footman.json", "Skeleton_Jump_runing" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_DYING_A, { "skeleton_footman.json", "Skeleton_Dying_A" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_DYING_B, { "skeleton_footman.json", "Skeleton_Dying_B" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_COMBAT_MODE, { "skeleton_footman.json", "Skeleton_1H_combat_mode" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_DODGE_BACKWARDS, { "skeleton_footman.json", "Skeleton_1H_dodge_backwards" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_DODGE_TO_LEFT, { "skeleton_footman.json", "Skeleton_1H_dodge_to_left" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_DODGE_TO_RIGHT, { "skeleton_footman.json", "Skeleton_1H_dodge_to_right" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_DUCK_BELOW_HIGH_SWING, { "skeleton_footman.json", "Skeleton_1H_duck_below_high_swing" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_PARRY_A, { "skeleton_footman.json", "Skeleton_1H_parry_A" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_PARRY_B, { "skeleton_footman.json", "Skeleton_1H_parry_B" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_PARRY_FROM_STRIGHT_DOWN, { "skeleton_footman.json", "Skeleton_1H_parry_from_stright_down" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_SHIELD_BLOCK, { "skeleton_footman.json", "Skeleton_1H_shield_block" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_SHIELD_BLOW, { "skeleton_footman.json", "Skeleton_1H_shield_blow" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_SWING_HIGH_STRAIGHT_DOWN, { "skeleton_footman.json", "Skeleton_1H_swing_high_straight_down" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_SWING_LEFT, { "skeleton_footman.json", "Skeleton_1H_swing_left" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_SWING_RIGHT, { "skeleton_footman.json", "Skeleton_1H_swing_right" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_THRUST, { "skeleton_footman.json", "Skeleton_1H_thrust" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_BANGING_SHIELD, { "skeleton_footman.json", "Skeleton_1H_banging_shield" }},
	    {SKELETON_FOOTMAN_JSON_SKELETON_1H_CHARGING, { "skeleton_footman.json", "Skeleton_1H_charging" }},
	    {BERSEKER_JSON_IDLE , { "berseker.json", "idle" }},
	    {BERSEKER_JSON_WALK , { "berseker.json", "walk" }},
	    {BERSEKER_JSON_RUN , { "berseker.json", "run" }},
	    {BERSEKER_JSON_ATTACK_IDLE , { "berseker.json", "attack_idle" }},
	    {BERSEKER_JSON_ATTACK_1 , { "berseker.json", "attack_1" }},
	    {BERSEKER_JSON_ATTACK_2 , { "berseker.json", "attack_2" }},
	    {BERSEKER_JSON_ATTACK_3 , { "berseker.json", "attack_3" }},
	    {BERSEKER_JSON_ATTACK_4 , { "berseker.json", "attack_4" }},
	    {BERSEKER_JSON_ATTACK_5 , { "berseker.json", "attack_5" }},
	    {BERSEKER_JSON_JUMP, { "berseker.json", "jump" }},
	    {BERSEKER_JSON_HIT , { "berseker.json", "hit" }},
	    {BERSEKER_JSON_DEATH , { "berseker.json", "death" }},
	    {BERSEKER_JSON_RECOVER , { "berseker.json", "recover" }},
	    {BERSEKER_JSON_TAUNT, { "berseker.json", "taunt" }},
	    {BERSEKER_JSON_STRAFE_RIGHT , { "berseker.json", "strafe_right" }},
	    {BERSEKER_JSON_STRAFE_LEFT , { "berseker.json", "strafe_left" }},
	    {BERSEKER_JSON_DODGE_RIGHT , { "berseker.json", "dodge_right" }},
    };
  }
}
