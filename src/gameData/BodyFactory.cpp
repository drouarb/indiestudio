//
// BodyFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 16:50:32 2016 Alexis Trouve
// Last update Sat Jun  4 20:07:38 2016 Alexis Trouve
//

#include <iostream>
#include <gameData/Spell/SpellFactory.hh>
#include <gameData/TextureName.hh>

using namespace gauntlet;

BodyFactory::BodyFactory()
{}

BodyFactory::BodyFactory(world::World *nworld, std::vector<world::AbstractAI*>& nAIs)
{
  world = nworld;
  AIs = nAIs;
  fillCreatureTab();
  fillGameObjectTab();
  fillPlayerTab();
}

BodyFactory::~BodyFactory()
{
}

int			BodyFactory::giveNextId()
{
  static int		nextId = -1;
  
  nextId++;
  return (nextId);
}

void			BodyFactory::fillPlayerTab()
{
  setBarbare();
  setElf();
  setWizard();
  setValkyrie();
}

void			BodyFactory::fillCreatureTab()
{
  setDraugr();
  setSkeleton();
  setSkeletonArcher();
  setSkeletonWarlord();
  setSkeletonWizard();
}

void			BodyFactory::fillGameObjectTab()
{
  setPorteLight();
  setDoor();
  setKey();
  setHealthPotion();
  setSpeedPotion();
  setPowerPotion();
}

void			BodyFactory::setBarbare()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Barbare");
  player->stats.HP = 200;
  player->stats.normalHP = 200;
  player->stats.speed = 11.0;
  player->stats.normalSpeed = 11.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->spellBook.addSpell(SpellFactory::BARBARIAN_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::BARBARIAN_TORNADO, player);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  player->changeOrientation(90);
  player->soundEffect[ABody::ATTACK] = {
          SoundName::MALE_ATTACK_1,
          SoundName::MALE_ATTACK_2,
          SoundName::MALE_HEAVY_ATTACK,
          SoundName::MALE_HEAVY_ATTACK_2,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::WOUND] = {
          SoundName::MALE_WOUNDED,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::DEATH] = {
          SoundName::MALE_DEATH,
          SoundName::SOUND_NONE
  };
  player->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::BERSEKER_ATTACK_1,
          animations::AnimationsListJson::BERSEKER_ATTACK_2,
          animations::AnimationsListJson::BERSEKER_ATTACK_3,
          //animations::AnimationsListJson::BERSEKER_ATTACK_4,
          //animations::AnimationsListJson::BERSEKER_ATTACK_5
  };
  player->setDeath(animations::AnimationsListJson::BERSEKER_DEATH);
  player->setIdle(animations::AnimationsListJson::BERSEKER_IDLE);
  player->setRunning(animations::AnimationsListJson::BERSEKER_RUN);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setElf()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Elf");
  player->stats.HP = 150;
  player->stats.normalHP = 150;
  player->stats.speed = 14.0;
  player->stats.normalSpeed = 14.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  player->changeOrientation(0);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setWizard()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Mage");
  player->stats.HP = 80;
  player->stats.normalHP = 80;
  player->stats.speed = 12.0;
  player->stats.normalSpeed = 12.0;
  player->stats.attackModifier = 1.2;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  player->changeOrientation(0);
  player->spellBook.addSpell(SpellFactory::WIZARD_FIREBALL, player);
  player->spellBook.addSpell(SpellFactory::WIZARD_FIRECONE, player);
  player->setMeshId(EntityName::SKELETON_FOOTMAN);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->soundEffect[ABody::ATTACK] = {
          SoundName::FIRE_SMALL,
          SoundName::FIRE_BIG,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::WOUND] = {
          SoundName::MALE_2_WOUNDED,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::DEATH] = {
          SoundName::MALE_2_DEATH,
          SoundName::SOUND_NONE
  };
  player->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_ARCHIER_SHOTING
  };
  player->setDeath(animations::AnimationsListJson::SKELETON_ARCHIER_DYING_B);
  player->setIdle(animations::AnimationsListJson::SKELETON_ARCHIER_IDLE);
  player->setRunning(animations::AnimationsListJson::SKELETON_ARCHIER_RUN);
  player->setMeshId(EntityName::SKELETON_ARCHER);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

/*void			BodyFactory::setWizard()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Mage");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 12.0;
  player->stats.normalSpeed = 12.0;
  player->stats.attackModifier = 1.2;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  player->changeOrientation(0);
  player->spellBook.addSpell(SpellFactory::WIZARD_FIREBALL, player);
  player->spellBook.addSpell(SpellFactory::WIZARD_FIRECONE, player);
  player->setMeshId(EntityName::SKELETON_FOOTMAN);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->soundEffect[ABody::ATTACK] = {
          SoundName::FIRE_SMALL,
          SoundName::FIRE_BIG,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::WOUND] = {
          SoundName::MALE_2_WOUNDED,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::DEATH] = {
          SoundName::MALE_2_DEATH,
          SoundName::SOUND_NONE
  };
  player->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_SORCERER_BUFF_SPELL_A,
          animations::AnimationsListJson::SKELETON_SORCERER_BUFF_SPELL_B,
          animations::AnimationsListJson::SKELETON_SORCERER_FIRE_BALL_SPELL,
          animations::AnimationsListJson::SKELETON_SORCERER_MAGIC_LIGHT_SPELL,
          animations::AnimationsListJson::SKELETON_SORCERER_SPELL_CAST_A,
          animations::AnimationsListJson::SKELETON_SORCERER_STAFF_EARTHQUAKE_SPELL
  };
  player->animations[ABody::DEATH] = {
          animations::AnimationsListJson::SKELETON_SORCERER_DYING_A
  };
  player->setIdle(animations::AnimationsListJson::SKELETON_SORCERER_IDLE);
  player->setRunning(animations::AnimationsListJson::SKELETON_SORCERER_RUN);
  player->setMeshId(EntityName::SKELETON_SORCERER);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
  }*/

void			BodyFactory::setValkyrie()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Valkyrie");
  player->stats.HP = 250;
  player->stats.normalHP = 250;
  player->stats.speed = 9.0;
  player->stats.normalSpeed = 9.0;
  player->stats.attackModifier = 1.0;
  player->spellBook.addSpell(SpellFactory::VALKYRIA_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::VALKYRIA_DASH, player);
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(25.0, 25.0));
  player->changeOrientation(0);
  player->soundEffect[ABody::ATTACK] = {
          SoundName::FEMALE_ATTACK,
          SoundName::FEMALE_HEAVY_ATTACK_2,
          SoundName::FEMALE_HEAVY_ATTACK_3,
          SoundName::FEMALE_HEAVY_ATTACK_4,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::WOUND] = {
          SoundName::FEMALE_HEAVY_ATTACK,
          SoundName::SOUND_NONE
  };
  player->soundEffect[ABody::DEATH] = {
          SoundName::FEMALE_DEATH,
          SoundName::SOUND_NONE
  };
  player->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::VALKYRIE_ATTACK_1,
          animations::AnimationsListJson::VALKYRIE_ATTACK_2,
          animations::AnimationsListJson::VALKYRIE_ATTACK_3,
          //animations::AnimationsListJson::VALKYRIE_ATTACK_4,
          //animations::AnimationsListJson::VALKYRIE_ATTACK_5
  };
  player->setDeath(animations::AnimationsListJson::VALKYRIE_DEATH);
  player->setIdle(animations::AnimationsListJson::VALKYRIE_IDLE);
  player->setRunning(animations::AnimationsListJson::VALKYRIE_RUN);
  player->setMeshId(EntityName::VALKYRIE);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setSkeleton()
{
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("Skeleton");
  crea->stats.HP = 100;
  crea->stats.normalHP = 100;
  crea->stats.speed = 6.0;
  crea->stats.normalSpeed = 6.0;
  crea->stats.attackModifier = 0.6;
  crea->spellBook.addSpell(SpellFactory::SIMPLE_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(22.0, 22.0));
  crea->changeOrientation(0);
  crea->soundEffect[ABody::ATTACK] = {
          SoundName::ZOMBIE_1,
          SoundName::ZOMBIE_2,
          SoundName::ZOMBIE_3,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::WOUND] = {
          SoundName::GHOST_1,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::DEATH] = {
          SoundName::GHOST_6,
          SoundName::SOUND_NONE
  };
  crea->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_FOOTMAN_SWING_LEFT,
          animations::AnimationsListJson::SKELETON_FOOTMAN_SWING_RIGHT,
          animations::AnimationsListJson::SKELETON_FOOTMAN_SWING_HIGH_STRAIGHT_DOWN,
//          animations::AnimationsListJson::SKELETON_FOOTMAN_THRUST,
//          animations::AnimationsListJson::SKELETON_FOOTMAN_HIT_FROM_BACK,
//          animations::AnimationsListJson::SKELETON_FOOTMAN_HIT_FROM_FRONT
  };
  crea->setDeath(animations::AnimationsListJson::SKELETON_FOOTMAN_DYING_A);
  crea->setIdle(animations::AnimationsListJson::SKELETON_FOOTMAN_IDLE);
  crea->setRunning(animations::AnimationsListJson::SKELETON_FOOTMAN_RUN);
  crea->setMeshId(EntityName::SKELETON_FOOTMAN);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(MELEEBASICAI);
  bodyTab.push_back(crea);
}

void			BodyFactory::setSkeletonWarlord()
{
  Spawner		*crea;

  crea = new Spawner(-1, world);
  crea->setName("SkeletonWarlord");
  crea->stats.HP = 400;
  crea->stats.normalHP = 400;
  crea->stats.speed = 6.0;
  crea->stats.normalSpeed = 6.0;
  crea->stats.attackModifier = 1.5;
  crea->spellBook.addSpell(SpellFactory::SIMPLE_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(50.0, 50.0));
  crea->changeOrientation(0);
  crea->soundEffect[ABody::ATTACK] = {
          SoundName::ZOMBIE_1,
          SoundName::ZOMBIE_2,
          SoundName::ZOMBIE_3,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::WOUND] = {
          SoundName::GHOST_1,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::DEATH] = {
          SoundName::GHOST_6,
          SoundName::SOUND_NONE
  };
  crea->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_WARLORD_SPECAL_ATTACK_A,
          animations::AnimationsListJson::SKELETON_WARLORD_SPECAL_ATTACK_B,
          animations::AnimationsListJson::SKELETON_WARLORD_SWING_MID_LEFT,
          animations::AnimationsListJson::SKELETON_WARLORD_SWING_MID_RIGHT,
          animations::AnimationsListJson::SKELETON_WARLORD_SWORD_SWING_HIGH_STRAIGHT_DOWN,
          animations::AnimationsListJson::SKELETON_WARLORD_SWORD_THRUST_MID,
//          animations::AnimationsListJson::SKELETON_WARLORD_HIT_FROM_BACK,
//          animations::AnimationsListJson::SKELETON_WARLORD_HIT_FROM_FRONT
  };
  crea->setDeath(animations::AnimationsListJson::SKELETON_WARLORD_DYING_A);
  crea->setIdle(animations::AnimationsListJson::SKELETON_WARLORD_IDLE);
  crea->setRunning(animations::AnimationsListJson::SKELETON_WARLORD_RUN);
  crea->setMeshId(EntityName::SKELETON_WARLORD);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(SPAWNERAI);
  crea->setSpawnCoolDown(5);
  crea->setSpawnCoolDownBase(5);
  crea->setMinionName("Skeleton");
  crea->setMaxSpawn(6);
  bodyTab.push_back(crea);
}

void			BodyFactory::setSkeletonArcher()
{
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("SkeletonArcher");
  crea->stats.HP = 100;
  crea->stats.normalHP = 100;
  crea->stats.speed = 6.0;
  crea->stats.normalSpeed = 6.0;
  crea->stats.attackModifier = 0.2;
  crea->spellBook.addSpell(SpellFactory::RANGER_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(50.0, 50.0));
  crea->changeOrientation(0);
  crea->soundEffect[ABody::ATTACK] = {
          SoundName::ZOMBIE_1,
          SoundName::ZOMBIE_2,
          SoundName::ZOMBIE_3,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::WOUND] = {
          SoundName::GHOST_1,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::DEATH] = {
          SoundName::GHOST_6,
          SoundName::SOUND_NONE
  };
  crea->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_ARCHIER_SHOTING
  };
  crea->setDeath(animations::AnimationsListJson::SKELETON_ARCHIER_DYING_B);
  crea->setIdle(animations::AnimationsListJson::SKELETON_ARCHIER_IDLE);
  crea->setRunning(animations::AnimationsListJson::SKELETON_ARCHIER_RUN);
  crea->setMeshId(EntityName::SKELETON_ARCHER);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(MELEEBASICAI);
  bodyTab.push_back(crea);
}

void			BodyFactory::setSkeletonWizard()
{
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("SkeletonWizard");
  crea->stats.HP = 100;
  crea->stats.normalHP = 100;
  crea->stats.speed = 6.0;
  crea->stats.normalSpeed = 6.0;
  crea->stats.attackModifier = 0.2;
  crea->spellBook.addSpell(SpellFactory::ICEBALL, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(50.0, 50.0));
  crea->changeOrientation(0);
  crea->soundEffect[ABody::ATTACK] = {
          SoundName::ZOMBIE_1,
          SoundName::ZOMBIE_2,
          SoundName::ZOMBIE_3,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::WOUND] = {
          SoundName::GHOST_1,
          SoundName::SOUND_NONE
  };
  crea->soundEffect[ABody::DEATH] = {
          SoundName::GHOST_6,
          SoundName::SOUND_NONE
  };
  crea->animations[ABody::ATTACK] = {
          animations::AnimationsListJson::SKELETON_SORCERER_BUFF_SPELL_A,
          animations::AnimationsListJson::SKELETON_SORCERER_BUFF_SPELL_B,
          animations::AnimationsListJson::SKELETON_SORCERER_FIRE_BALL_SPELL,
          animations::AnimationsListJson::SKELETON_SORCERER_MAGIC_LIGHT_SPELL,
          animations::AnimationsListJson::SKELETON_SORCERER_SPELL_CAST_A,
          animations::AnimationsListJson::SKELETON_SORCERER_STAFF_EARTHQUAKE_SPELL
  };
  crea->setDeath(animations::AnimationsListJson::SKELETON_SORCERER_DYING_A);
  crea->setIdle(animations::AnimationsListJson::SKELETON_SORCERER_IDLE);
  crea->setRunning(animations::AnimationsListJson::SKELETON_SORCERER_RUN);
  crea->setMeshId(EntityName::SKELETON_SORCERER);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(MELEEBASICAI);
  bodyTab.push_back(crea);
}

void			BodyFactory::setDraugr()
{
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("Draugr");
  crea->stats.HP = 400;
  crea->stats.normalHP = 400;
  crea->stats.speed = 6.0;
  crea->stats.normalSpeed = 6.0;
  crea->stats.attackModifier = 0.6;
  crea->spellBook.addSpell(SpellFactory::SIMPLE_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(10.0, 10.0));
  crea->changeOrientation(0);
  crea->setMeshId(EntityName::BERSERK);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(MELEEBASICAI);
  bodyTab.push_back(crea);
}

void            BodyFactory::setKey()
{
  GameObject		*obj;
  Item              *key;

  key = new Item();
  key->setKey(true);
  key->setName("Key");
  obj = new GameObject(-1, world);
  obj->setBasicParameters("Key", true, false);
  obj->setCollide(false);
  obj->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  obj->changePos(std::make_pair(-1, -1));
  obj->changeOrientation(90);
  obj->setMeshId(EntityName::CHEST);
  obj->setTextureId(TextureName::TEXTURE_NONE);
  obj->addItem(*key);
  bodyTab.push_back(obj);
}

void             BodyFactory::setSpeedPotion()
{
  GameObject		*obj;
  Item              *item;

  item = new Item();
  item->setKey(false);
  item->setName("Speed Potion");
  item->setAsConsummable();
  item->setPrice(10);
  item->modifyStats()->speed = 10;
  obj = new GameObject(-1, world);
  obj->setBasicParameters("SpeedPotion", true, false);
  obj->setCollide(false);
  obj->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  obj->changePos(std::make_pair(-1, -1));
  obj->changeOrientation(90);
  obj->setMeshId(EntityName::CHEST);
  obj->setTextureId(TextureName::TEXTURE_NONE);
  obj->addItem(*item);
  bodyTab.push_back(obj);
}

void            BodyFactory::setHealthPotion()
{
  GameObject		*obj;
  Item              *item;

  item = new Item();
  item->setKey(false);
  item->setName("HealthPotion");
  item->setAsConsummable();
  item->setPrice(10);
  item->modifyStats()->HP = 100;
  obj = new GameObject(-1, world);
  obj->setBasicParameters("Potion", true, false);
  obj->setCollide(false);
  obj->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  obj->changePos(std::make_pair(-1, -1));
  obj->changeOrientation(90);
  obj->setMeshId(EntityName::CHEST);
  obj->setTextureId(TextureName::TEXTURE_NONE);
  obj->addItem(*item);
  bodyTab.push_back(obj);
}

void            BodyFactory::setPowerPotion()
{
  GameObject		*obj;
  Item              *item;

  item = new Item();
  item->setKey(false);
  item->setName("PowerPotion");
  item->setAsConsummable();
  item->setPrice(10);
  item->modifyStats()->attackModifier = 1;
  obj = new GameObject(-1, world);
  obj->setBasicParameters("Potion", true, false);
  obj->setCollide(false);
  obj->changeSize(std::make_pair(PLAYER_SIZE, PLAYER_SIZE));
  obj->changePos(std::make_pair(-1, -1));
  obj->changeOrientation(90);
  obj->setMeshId(EntityName::CHEST);
  obj->setTextureId(TextureName::TEXTURE_NONE);
  obj->addItem(*item);
  bodyTab.push_back(obj);
}


void            BodyFactory::setDoor()
{
  GameObject        *obj;

  obj = new GameObject(-1, world);
  obj->setBasicParameters("Door", false, true);
  obj->setCollide(true);
  obj->changeSize(std::make_pair(10.0, 10.0));
  obj->changePos(std::make_pair(-1, -1));
  obj->changeOrientation(90);
  obj->setIdle(animations::AnimationsListJson::DOOR_OPEN);
  obj->setMeshId(EntityName::DOOR);
  obj->setTextureId(TextureName::TEXTURE_NONE);
  bodyTab.push_back(obj);
}

void			BodyFactory::setPorteLight()
{
  GameObject		*obj;

  obj = new GameObject(-1, world);
  obj->setName("PorteLight");
  obj->setCollide(true);
  obj->changePos(std::make_pair(-1, -1));
  obj->changeSize(std::make_pair(160.0, 160.0));
  obj->changeOrientation(0);
  bodyTab.push_back(obj);
}

ABody	*BodyFactory::giveBody(const std::string& name)
{
  unsigned int	i;
  int		j;
  ABody		*body;
  Actor		*actor;

  i = 0;
  while (i < bodyTab.size())
    {
      if (name == bodyTab[i]->getName())
	{
	  body = bodyTab[i]->clone(giveNextId());
	  if ((actor = dynamic_cast<Actor*>(body)) != NULL)
	    {
	      j = actor->getIdAI();
	      if (j != NOAI)
		{
		  std::cout << "size:" << AIs.size() << std::endl;
		  std::cout << "j:" << j << std::endl;
		  AIs[j]->setNewAI(actor);
		}
	    }
	  return (body);
	}
      ++i;
    }
  return (NULL);
}
