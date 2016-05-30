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
      virtual ~Animation()
      { }

      virtual bool update(double elapsedTime) = 0;

      virtual void reset() = 0;

      virtual std::string const &getName() const = 0;
    };

    class JSONAnimation : public Animation
    {
     private:
      JSON::JsonObj *jsonObj;
      const std::string &filename;
      Ogre::AnimationState *animationState;
      double begin = -1;
      double end = -1;
      double currentTimePosition = 0;

     private:
      void findProprerties(const std::string &animationName);

     public:
      JSONAnimation(const std::string &filename,
		    const std::string &animationName, Ogre::AnimationState *,
		    bool loop);

      ~JSONAnimation();


      virtual bool update(double elapsedTime) final;

      virtual std::string const &getName() const final;

      std::string readJson(const std::string &filename);

      virtual void reset() final;
    };

    /*
     * \quote
     * <Type, <filename, animationName>>
     */
    static const std::map<animations::AnimationsListJson, std::pair<std::string, std::string>> jsonMap = {
	    {SKELETON_SORCERER_SWING_RIGHT,                   {"skeleton_sorcerer.json", "M_SKELETON_SWING_RIGHT"}},
	    {SKELETON_SORCERER_COMBAT_MODE_B,                 {"skeleton_sorcerer.json", "M_SKELETON_COMBAT_MODE_B"}},
	    {SKELETON_SORCERER_DUCK_BELOW_SWING,              {"skeleton_sorcerer.json", "M_SKELETON_DUCK_BELOW_SWING"}},
	    {SKELETON_SORCERER_MAGIC_LIGHT_SPELL,             {"skeleton_sorcerer.json", "M_SKELETON_MAGIC_LIGHT_SPELL"}},
	    {SKELETON_SORCERER_MAGIC_SHOT_STRIGHT,            {"skeleton_sorcerer.json", "M_SKELETON_MAGIC_SHOT_STRIGHT"}},
	    {SKELETON_SORCERER_COMBAT_MODE_C,                 {"skeleton_sorcerer.json", "M_SKELETON_COMBAT_MODE_C"}},
	    {SKELETON_SORCERER_BUFF_SPELL_A,                  {"skeleton_sorcerer.json", "M_SKELETON_BUFF_SPELL_A"}},
	    {SKELETON_SORCERER_BUFF_SPELL_B,                  {"skeleton_sorcerer.json", "M_SKELETON_BUFF_SPELL_B"}},
	    {SKELETON_SORCERER_FIRE_BALL_SPELL,               {"skeleton_sorcerer.json", "M_SKELETON_FIRE_BALL_SPELL"}},
	    {SKELETON_SORCERER_SPELL_CAST_A,                  {"skeleton_sorcerer.json", "M_SKELETON_SPELL_CAST_A"}},
	    {SKELETON_SORCERER_MAKING_POTION,                 {"skeleton_sorcerer.json", "M_SKELETON_MAKING_POTION"}},
	    {SKELETON_WARLORD_WARLORD,                        {"skeleton_warlord.json",  "SKELETON_WARLORD"}},
	    {SKELETON_WARLORD_IDLE,                           {"skeleton_warlord.json",  "SKELETON_IDLE"}},
	    {SKELETON_WARLORD_USE_OBJECT,                     {"skeleton_warlord.json",  "SKELETON_USE_OBJECT"}},
	    {SKELETON_WARLORD_ANGER,                          {"skeleton_warlord.json",  "SKELETON_ANGER"}},
	    {SKELETON_WARLORD_DRINKING,                       {"skeleton_warlord.json",  "SKELETON_DRINKING"}},
	    {SKELETON_WARLORD_HIT_FROM_BACK,                  {"skeleton_warlord.json",  "SKELETON_HIT_FROM_BACK"}},
	    {SKELETON_WARLORD_HIT_FROM_FRONT,                 {"skeleton_warlord.json",  "SKELETON_HIT_FROM_FRONT"}},
	    {SKELETON_WARLORD_LOOKING_AROUND,                 {"skeleton_warlord.json",  "SKELETON_LOOKING_AROUND"}},
	    {SKELETON_WARLORD_POINTING_A,                     {"skeleton_warlord.json",  "SKELETON_POINTING_A"}},
	    {SKELETON_WARLORD_SALUTE,                         {"skeleton_warlord.json",  "SKELETON_SALUTE"}},
	    {SKELETON_WARLORD_TALKING,                        {"skeleton_warlord.json",  "SKELETON_TALKING"}},
	    {SKELETON_WARLORD_THINKING,                       {"skeleton_warlord.json",  "SKELETON_THINKING"}},
	    {SKELETON_WARLORD_TRACKING,                       {"skeleton_warlord.json",  "SKELETON_TRACKING"}},
	    {SKELETON_WARLORD_SIT_DOWN,                       {"skeleton_warlord.json",  "SKELETON_SIT_DOWN"}},
	    {SKELETON_WARLORD_SITTING,                        {"skeleton_warlord.json",  "SKELETON_SITTING"}},
	    {SKELETON_WARLORD_CAME_UP,                        {"skeleton_warlord.json",  "SKELETON_CAME_UP"}},
	    {SKELETON_WARLORD_GOING_ASLEEP,                   {"skeleton_warlord.json",  "SKELETON_GOING_ASLEEP"}},
	    {SKELETON_WARLORD_SLEEPING,                       {"skeleton_warlord.json",  "SKELETON_SLEEPING"}},
	    {SKELETON_WARLORD_WAKING_UP,                      {"skeleton_warlord.json",  "SKELETON_WAKING_UP"}},
	    {SKELETON_WARLORD_WALKING_BACK,                   {"skeleton_warlord.json",  "SKELETON_WALKING_BACK"}},
	    {SKELETON_WARLORD_CLIMBING_LADDER,                {"skeleton_warlord.json",  "SKELETON_CLIMBING_LADDER"}},
	    {SKELETON_WARLORD_CROUCHING,                      {"skeleton_warlord.json",  "SKELETON_CROUCHING"}},
	    {SKELETON_WARLORD_FALLING_DOWN,                   {"skeleton_warlord.json",  "SKELETON_FALLING_DOWN"}},
	    {SKELETON_WARLORD_MOVING_LEFT,                    {"skeleton_warlord.json",  "SKELETON_MOVING_LEFT"}},
	    {SKELETON_WARLORD_MOVING_RIGHT,                   {"skeleton_warlord.json",  "SKELETON_MOVING_RIGHT"}},
	    {SKELETON_WARLORD_SNEAKING,                       {"skeleton_warlord.json",  "SKELETON_SNEAKING"}},
	    {SKELETON_WARLORD_RUN,                            {"skeleton_warlord.json",  "SKELETON_RUN"}},
	    {SKELETON_WARLORD_JUMP_RUNING,                    {"skeleton_warlord.json",  "SKELETON_JUMP_RUNING"}},
	    {SKELETON_WARLORD_DYING_A,                        {"skeleton_warlord.json",  "SKELETON_DYING_A"}},
	    {SKELETON_WARLORD_WALK,                           {"skeleton_warlord.json",  "SKELETON_WALK"}},
	    {SKELETON_WARLORD_WITH_WEAPON_WALK,               {"skeleton_warlord.json",  "2H_SKELETON_WITH_WEAPON_WALK"}},
	    {SKELETON_WARLORD_CHARGING,                       {"skeleton_warlord.json",  "2H_SKELETON_CHARGING"}},
	    {SKELETON_WARLORD_COMBAT_MODE,                    {"skeleton_warlord.json",  "2H_SKELETON_COMBAT_MODE"}},
	    {SKELETON_WARLORD_DODGE_BACKWARDS,                {"skeleton_warlord.json",  "2H_SKELETON_DODGE_BACKWARDS"}},
	    {SKELETON_WARLORD_DODGE_TO_LEFT,                  {"skeleton_warlord.json",  "2H_SKELETON_DODGE_TO_LEFT"}},
	    {SKELETON_WARLORD_DODGE_TO_RIGH,                  {"skeleton_warlord.json",  "2H_SKELETON_DODGE_TO_RIGH"}},
	    {SKELETON_WARLORD_DUCK_BELOW_HIGH_SWING,          {"skeleton_warlord.json",  "2H_SKELETON_DUCK_BELOW_HIGH_SWING"}},
	    {SKELETON_WARLORD_PARRY_FROM_STRIGHT_DOWN,        {"skeleton_warlord.json",  "2H_SKELETON_PARRY_FROM_STRIGHT_DOWN"}},
	    {SKELETON_WARLORD_PARRY_LOW_FRONT,                {"skeleton_warlord.json",  "2H_SKELETON_PARRY_LOW_FRONT"}},
	    {SKELETON_WARLORD_PARRY_MID_LEFT,                 {"skeleton_warlord.json",  "2H_SKELETON_PARRY_MID_LEFT"}},
	    {SKELETON_WARLORD_SPECAL_ATTACK_A,                {"skeleton_warlord.json",  "2H_SKELETON_SPECAL_ATTACK_A"}},
	    {SKELETON_WARLORD_SPECAL_ATTACK_B,                {"skeleton_warlord.json",  "2H_SKELETON_SPECAL_ATTACK_B"}},
	    {SKELETON_WARLORD_SWING_MID_LEFT,                 {"skeleton_warlord.json",  "2H_SKELETON_SWING_MID_LEFT"}},
	    {SKELETON_WARLORD_SWING_MID_RIGHT,                {"skeleton_warlord.json",  "2H_SKELETON_SWING_MID_RIGHT"}},
	    {SKELETON_WARLORD_SWORD_SWING_HIGH_STRAIGHT_DOWN, {"skeleton_warlord.json",  "2H_SKELETON_SWORD_SWING_HIGH_STRAIGHT_DOWN"}},
	    {SKELETON_WARLORD_SWORD_THRUST_MID,               {"skeleton_warlord.json",  "2H_SKELETON_SWORD_THRUST_MID"}},
	    {SKELETON_SORCERER_IDLE,                          {"skeleton_sorcerer.json", "Skeleton_Idle"}},
	    {SKELETON_SORCERER_USE_OBJECT,                    {"skeleton_sorcerer.json", "Skeleton_Use_object"}},
	    {SKELETON_SORCERER_ANGER,                         {"skeleton_sorcerer.json", "Skeleton_anger"}},
	    {SKELETON_SORCERER_DRINKING,                      {"skeleton_sorcerer.json", "Skeleton_Drinking"}},
	    {SKELETON_SORCERER_HIT_FROM_BACK,                 {"skeleton_sorcerer.json", "Skeleton_Hit_from_back"}},
	    {SKELETON_SORCERER_HIT_FROM_FRONT,                {"skeleton_sorcerer.json", "Skeleton_Hit_from_front"}},
	    {SKELETON_SORCERER_LOOKING_AROUND,                {"skeleton_sorcerer.json", "Skeleton_Looking_around"}},
	    {SKELETON_SORCERER_POINTING_A,                    {"skeleton_sorcerer.json", "Skeleton_pointing_A"}},
	    {SKELETON_SORCERER_SALUTE,                        {"skeleton_sorcerer.json", "Skeleton_salute"}},
	    {SKELETON_SORCERER_TALKING,                       {"skeleton_sorcerer.json", "Skeleton_Talking"}},
	    {SKELETON_SORCERER_THINKING,                      {"skeleton_sorcerer.json", "Skeleton_thinking"}},
	    {SKELETON_SORCERER_TRACKING,                      {"skeleton_sorcerer.json", "Skeleton_Tracking"}},
	    {SKELETON_SORCERER_SIT_DOWN,                      {"skeleton_sorcerer.json", "Skeleton_sit_down"}},
	    {SKELETON_SORCERER_SITTING,                       {"skeleton_sorcerer.json", "Skeleton_sitting"}},
	    {SKELETON_SORCERER_CAME_UP,                       {"skeleton_sorcerer.json", "Skeleton_came_up"}},
	    {SKELETON_SORCERER_GOING_ASLEEP,                  {"skeleton_sorcerer.json", "Skeleton_Going_asleep"}},
	    {SKELETON_SORCERER_SLEEPING,                      {"skeleton_sorcerer.json", "Skeleton_sleeping"}},
	    {SKELETON_SORCERER_WAKING_UP,                     {"skeleton_sorcerer.json", "Skeleton_waking_up"}},
	    {SKELETON_SORCERER_WALKING_BACK,                  {"skeleton_sorcerer.json", "Skeleton_walking_back"}},
	    {SKELETON_SORCERER_CLIMBING_LADDER,               {"skeleton_sorcerer.json", "Skeleton_Climbing_ladder"}},
	    {SKELETON_SORCERER_CROUCHING,                     {"skeleton_sorcerer.json", "Skeleton_Crouching"}},
	    {SKELETON_SORCERER_FALLING_DOWN,                  {"skeleton_sorcerer.json", "Skeleton_falling_down"}},
	    {SKELETON_SORCERER_MOVING_LEFT,                   {"skeleton_sorcerer.json", "Skeleton_Moving_left"}},
	    {SKELETON_SORCERER_MOVING_RIGHT,                  {"skeleton_sorcerer.json", "Skeleton_Moving_right"}},
	    {SKELETON_SORCERER_SNEAKING,                      {"skeleton_sorcerer.json", "Skeleton_Sneaking"}},
	    {SKELETON_SORCERER_RUN,                           {"skeleton_sorcerer.json", "Skeleton_Run"}},
	    {SKELETON_SORCERER_JUMP_RUNING,                   {"skeleton_sorcerer.json", "Skeleton_Jump_runing"}},
	    {SKELETON_SORCERER_DYING_A,                       {"skeleton_sorcerer.json", "Skeleton_Dying_A"}},
	    {SKELETON_SORCERER_WALK,                          {"skeleton_sorcerer.json", "Skeleton_walk"}},
	    {SKELETON_SORCERER_COMBAT_MODE_A,                 {"skeleton_sorcerer.json", "M_skeleton_combat_mode_A"}},
	    {SKELETON_SORCERER_DODGE_TO_LEFT,                 {"skeleton_sorcerer.json", "M_skeleton_dodge_to_left"}},
	    {SKELETON_SORCERER_DODGE_TO_RIGHT,                {"skeleton_sorcerer.json", "M_skeleton_dodge_to_right"}},
	    {SKELETON_SORCERER_STAF_BLOCK,                    {"skeleton_sorcerer.json", "M_skeleton_staf_block"}},
	    {SKELETON_SORCERER_STAFF_EARTHQUAKE_SPELL,        {"skeleton_sorcerer.json", "M_skeleton_staff_earthquake_spell"}},
	    {SKELETON_SORCERER_STAFF_HIT,                     {"skeleton_sorcerer.json", "M_skeleton_staff_Hit"}},
	    {SKELETON_SORCERER_STRAIGHT_DOWN_HIT,             {"skeleton_sorcerer.json", "M_skeleton_straight_down_hit"}},
	    {SKELETON_SORCERER_SWING_RIGHT,                   {"skeleton_sorcerer.json", "M_skeleton_swing_right"}},
	    {SKELETON_SORCERER_COMBAT_MODE_B,                 {"skeleton_sorcerer.json", "M_skeleton_combat_mode_B"}},
	    {SKELETON_SORCERER_DUCK_BELOW_SWING,              {"skeleton_sorcerer.json", "M_skeleton_duck_below_swing"}},
	    {SKELETON_SORCERER_MAGIC_LIGHT_SPELL,             {"skeleton_sorcerer.json", "M_skeleton_magic_light_spell"}},
	    {SKELETON_SORCERER_MAGIC_SHOT_STRIGHT,            {"skeleton_sorcerer.json", "M_skeleton_magic_shot_stright"}},
	    {SKELETON_SORCERER_COMBAT_MODE_C,                 {"skeleton_sorcerer.json", "M_skeleton_combat_mode_C"}},
	    {SKELETON_SORCERER_BUFF_SPELL_A,                  {"skeleton_sorcerer.json", "M_skeleton_buff_spell_A"}},
	    {SKELETON_SORCERER_BUFF_SPELL_B,                  {"skeleton_sorcerer.json", "M_skeleton_buff_spell_B"}},
	    {SKELETON_SORCERER_FIRE_BALL_SPELL,               {"skeleton_sorcerer.json", "M_skeleton_fire_ball_spell"}},
	    {SKELETON_SORCERER_SPELL_CAST_A,                  {"skeleton_sorcerer.json", "M_skeleton_spell_cast_A"}},
	    {SKELETON_SORCERER_MAKING_POTION,                 {"skeleton_sorcerer.json", "M_skeleton_making_potion"}},
	    {SKELETON_ARCHIER_IDLE,                           {"skeleton_archier.json",  "Skeleton_Idle"}},
	    {SKELETON_ARCHIER_USE_OBJECT,                     {"skeleton_archier.json",  "Skeleton_Use_object"}},
	    {SKELETON_ARCHIER_ANGER,                          {"skeleton_archier.json",  "Skeleton_anger"}},
	    {SKELETON_ARCHIER_DRINKING,                       {"skeleton_archier.json",  "Skeleton_Drinking"}},
	    {SKELETON_ARCHIER_HIT_FROM_BACK,                  {"skeleton_archier.json",  "Skeleton_Hit_from_back"}},
	    {SKELETON_ARCHIER_HIT_FROM_FRONT,                 {"skeleton_archier.json",  "Skeleton_Hit_from_front"}},
	    {SKELETON_ARCHIER_LOOKING_AROUND,                 {"skeleton_archier.json",  "Skeleton_Looking_around"}},
	    {SKELETON_ARCHIER_POINTING_A,                     {"skeleton_archier.json",  "Skeleton_pointing_A"}},
	    {SKELETON_ARCHIER_SALUTE,                         {"skeleton_archier.json",  "Skeleton_salute"}},
	    {SKELETON_ARCHIER_TALKING,                        {"skeleton_archier.json",  "Skeleton_Talking"}},
	    {SKELETON_ARCHIER_THINKING,                       {"skeleton_archier.json",  "Skeleton_thinking"}},
	    {SKELETON_ARCHIER_TRACKING,                       {"skeleton_archier.json",  "Skeleton_Tracking"}},
	    {SKELETON_ARCHIER_SIT_DOWN,                       {"skeleton_archier.json",  "Skeleton_sit_down"}},
	    {SKELETON_ARCHIER_SITTING,                        {"skeleton_archier.json",  "Skeleton_sitting"}},
	    {SKELETON_ARCHIER_CAME_UP,                        {"skeleton_archier.json",  "Skeleton_came_up"}},
	    {SKELETON_ARCHIER_GOING_ASLEEP,                   {"skeleton_archier.json",  "Skeleton_Going_asleep"}},
	    {SKELETON_ARCHIER_SLEEPING,                       {"skeleton_archier.json",  "Skeleton_sleeping"}},
	    {SKELETON_ARCHIER_WAKING_UP,                      {"skeleton_archier.json",  "Skeleton_waking_up"}},
	    {SKELETON_ARCHIER_WALKING_BACK,                   {"skeleton_archier.json",  "Skeleton_walking_back"}},
	    {SKELETON_ARCHIER_CLIMBING_LADDER,                {"skeleton_archier.json",  "Skeleton_Climbing_ladder"}},
	    {SKELETON_ARCHIER_CROUCHING,                      {"skeleton_archier.json",  "Skeleton_Crouching"}},
	    {SKELETON_ARCHIER_FALLING_DOWN,                   {"skeleton_archier.json",  "Skeleton_falling_down"}},
	    {SKELETON_ARCHIER_MOVING_LEFT,                    {"skeleton_archier.json",  "Skeleton_Moving_left"}},
	    {SKELETON_ARCHIER_MOVING_RIGHT,                   {"skeleton_archier.json",  "Skeleton_Moving_right"}},
	    {SKELETON_ARCHIER_SNEAKING,                       {"skeleton_archier.json",  "Skeleton_Sneaking"}},
	    {SKELETON_ARCHIER_RUN,                            {"skeleton_archier.json",  "Skeleton_Run"}},
	    {SKELETON_ARCHIER_JUMP_RUNING,                    {"skeleton_archier.json",  "Skeleton_Jump_runing"}},
	    {SKELETON_ARCHIER_DYING_B,                        {"skeleton_archier.json",  "Skeleton_Dying_A"}},
	    {SKELETON_ARCHIER_SHOTING,                        {"skeleton_archier.json",  "Skeleton_archer_shoting"}},
	    {SKELETON_ARCHIER_WALK,                           {"skeleton_archier.json",  "Skeleton_walk"}},
	    {SKELETON_ARCHIER_DODGE_TO_LEFT,                  {"skeleton_archier.json",  "M_skeleton_dodge_to_left"}},
	    {SKELETON_ARCHIER_DODGE_TO_RIGHT,                 {"skeleton_archier.json",  "M_skeleton_dodge_to_right"}},
	    {SKELETON_FOOTMAN_IDLE,                           {"skeleton_footman.json",  "Skeleton_Idle"}},
	    {SKELETON_FOOTMAN_USE_OBJECT,                     {"skeleton_footman.json",  "Skeleton_Use_object"}},
	    {SKELETON_FOOTMAN_ANGER,                          {"skeleton_footman.json",  "Skeleton_anger"}},
	    {SKELETON_FOOTMAN_DRINKING,                       {"skeleton_footman.json",  "Skeleton_Drinking"}},
	    {SKELETON_FOOTMAN_HIT_FROM_BACK,                  {"skeleton_footman.json",  "Skeleton_Hit_from_back"}},
	    {SKELETON_FOOTMAN_HIT_FROM_FRONT,                 {"skeleton_footman.json",  "Skeleton_Hit_from_front"}},
	    {SKELETON_FOOTMAN_LOOKING_AROUND,                 {"skeleton_footman.json",  "Skeleton_Looking_around"}},
	    {SKELETON_FOOTMAN_POINTING_A,                     {"skeleton_footman.json",  "Skeleton_pointing_A"}},
	    {SKELETON_FOOTMAN_SALUTE,                         {"skeleton_footman.json",  "Skeleton_salute"}},
	    {SKELETON_FOOTMAN_TALKING,                        {"skeleton_footman.json",  "Skeleton_Talking"}},
	    {SKELETON_FOOTMAN_THINKING,                       {"skeleton_footman.json",  "Skeleton_thinking"}},
	    {SKELETON_FOOTMAN_TRACKING,                       {"skeleton_footman.json",  "Skeleton_Tracking"}},
	    {SKELETON_FOOTMAN_SIT_DOWN,                       {"skeleton_footman.json",  "Skeleton_sit_down"}},
	    {SKELETON_FOOTMAN_SITTING,                        {"skeleton_footman.json",  "Skeleton_sitting"}},
	    {SKELETON_FOOTMAN_CAME_UP,                        {"skeleton_footman.json",  "Skeleton_came_up"}},
	    {SKELETON_FOOTMAN_GOING_ASLEEP,                   {"skeleton_footman.json",  "Skeleton_Going_asleep"}},
	    {SKELETON_FOOTMAN_SLEEPING,                       {"skeleton_footman.json",  "Skeleton_sleeping"}},
	    {SKELETON_FOOTMAN_WAKING_UP,                      {"skeleton_footman.json",  "Skeleton_waking_up"}},
	    {SKELETON_FOOTMAN_WALKING_BACK,                   {"skeleton_footman.json",  "Skeleton_walking_back"}},
	    {SKELETON_FOOTMAN_CLIMBING_LADDER,                {"skeleton_footman.json",  "Skeleton_Climbing_ladder"}},
	    {SKELETON_FOOTMAN_CROUCHING,                      {"skeleton_footman.json",  "Skeleton_Crouching"}},
	    {SKELETON_FOOTMAN_FALLING_DOWN,                   {"skeleton_footman.json",  "Skeleton_falling_down"}},
	    {SKELETON_FOOTMAN_MOVING_LEFT,                    {"skeleton_footman.json",  "Skeleton_Moving_left"}},
	    {SKELETON_FOOTMAN_MOVING_RIGHT,                   {"skeleton_footman.json",  "Skeleton_Moving_right"}},
	    {SKELETON_FOOTMAN_SNEAKING,                       {"skeleton_footman.json",  "Skeleton_Sneaking"}},
	    {SKELETON_FOOTMAN_RUN,                            {"skeleton_footman.json",  "Skeleton_Run"}},
	    {SKELETON_FOOTMAN_JUMP_RUNING,                    {"skeleton_footman.json",  "Skeleton_Jump_runing"}},
	    {SKELETON_FOOTMAN_DYING_A,                        {"skeleton_footman.json",  "Skeleton_Dying_A"}},
	    {SKELETON_FOOTMAN_DYING_B,                        {"skeleton_footman.json",  "Skeleton_Dying_B"}},
	    {SKELETON_FOOTMAN_COMBAT_MODE,                    {"skeleton_footman.json",  "Skeleton_1H_combat_mode"}},
	    {SKELETON_FOOTMAN_DODGE_BACKWARDS,                {"skeleton_footman.json",  "Skeleton_1H_dodge_backwards"}},
	    {SKELETON_FOOTMAN_DODGE_TO_LEFT,                  {"skeleton_footman.json",  "Skeleton_1H_dodge_to_left"}},
	    {SKELETON_FOOTMAN_DODGE_TO_RIGHT,                 {"skeleton_footman.json",  "Skeleton_1H_dodge_to_right"}},
	    {SKELETON_FOOTMAN_DUCK_BELOW_HIGH_SWING,          {"skeleton_footman.json",  "Skeleton_1H_duck_below_high_swing"}},
	    {SKELETON_FOOTMAN_PARRY_A,                        {"skeleton_footman.json",  "Skeleton_1H_parry_A"}},
	    {SKELETON_FOOTMAN_PARRY_B,                        {"skeleton_footman.json",  "Skeleton_1H_parry_B"}},
	    {SKELETON_FOOTMAN_PARRY_FROM_STRIGHT_DOWN,        {"skeleton_footman.json",  "Skeleton_1H_parry_from_stright_down"}},
	    {SKELETON_FOOTMAN_SHIELD_BLOCK,                   {"skeleton_footman.json",  "Skeleton_1H_shield_block"}},
	    {SKELETON_FOOTMAN_SHIELD_BLOW,                    {"skeleton_footman.json",  "Skeleton_1H_shield_blow"}},
	    {SKELETON_FOOTMAN_SWING_HIGH_STRAIGHT_DOWN,       {"skeleton_footman.json",  "Skeleton_1H_swing_high_straight_down"}},
	    {SKELETON_FOOTMAN_SWING_LEFT,                     {"skeleton_footman.json",  "Skeleton_1H_swing_left"}},
	    {SKELETON_FOOTMAN_SWING_RIGHT,                    {"skeleton_footman.json",  "Skeleton_1H_swing_right"}},
	    {SKELETON_FOOTMAN_THRUST,                         {"skeleton_footman.json",  "Skeleton_1H_thrust"}},
	    {SKELETON_FOOTMAN_BANGING_SHIELD,                 {"skeleton_footman.json",  "Skeleton_1H_banging_shield"}},
	    {SKELETON_FOOTMAN_CHARGING,                       {"skeleton_footman.json",  "Skeleton_1H_charging"}},

	    {BERSEKER_IDLE,                                   {"berseker.json",          "idle"}},
	    {BERSEKER_WALK,                                   {"berseker.json",          "walk"}},
	    {BERSEKER_RUN,                                    {"berseker.json",          "run"}},
	    {BERSEKER_ATTACK_IDLE,                            {"berseker.json",          "attack_idle"}},
	    {BERSEKER_ATTACK_1,                               {"berseker.json",          "attack_1"}},
	    {BERSEKER_ATTACK_2,                               {"berseker.json",          "attack_2"}},
	    {BERSEKER_ATTACK_3,                               {"berseker.json",          "attack_3"}},
	    {BERSEKER_ATTACK_4,                               {"berseker.json",          "attack_4"}},
	    {BERSEKER_ATTACK_5,                               {"berseker.json",          "attack_5"}},
	    {BERSEKER_JUMP,                                   {"berseker.json",          "jump"}},
	    {BERSEKER_HIT,                                    {"berseker.json",          "hit"}},
	    {BERSEKER_DEATH,                                  {"berseker.json",          "death"}},
	    {BERSEKER_RECOVER,                                {"berseker.json",          "recover"}},
	    {BERSEKER_TAUNT,                                  {"berseker.json",          "taunt"}},
	    {BERSEKER_STRAFE_RIGHT,                           {"berseker.json",          "strafe_right"}},
	    {BERSEKER_STRAFE_LEFT,                            {"berseker.json",          "strafe_left"}},
	    {BERSEKER_DODGE_RIGHT,                            {"berseker.json",          "dodge_right"}},
    };
  }
}
