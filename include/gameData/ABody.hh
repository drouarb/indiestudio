//
// ABody.hh for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:06:15 2016 Alexis Trouve
// Last update Fri Jun  3 22:26:49 2016 Alexis Trouve
//

#ifndef ABODY_HH_
# define ABODY_HH_

#include "Math.hh"
#include "EntityName.hh"
#include "SoundName.hh"
#include "AnimationsList.hh"
#include <vector>

namespace gauntlet
{
    namespace world {
    class World;
    };
  class ABody
  {
  protected:
    bool			            collideActive;
    int				            id;
    std::pair<double, double>	coord;
    std::pair<double, double>	size;
    short			            orientation;
    std::string			        name;
    world::World		        *world;
    int                         model;
    int                         texture;
    unsigned long               cooldown;
    animations::AnimationsListJson idle;
    animations::AnimationsListJson running;

  public:
    enum    soundType {
            ATTACK = 0,
            WOUND = 1,
            DEATH = 2,
            SIZE = 3
    };

    std::vector<animations::AnimationsListJson>     animations[SIZE];
    std::vector<SoundName>   soundEffect[SIZE];

  public:
    ABody(int nid);
    virtual ~ABody();

    virtual bool			recharged();
    virtual void			changePos(const std::pair<double, double>& ncoord);
    virtual void			changeSize(const std::pair<double, double>& nsize);
    virtual void			changeOrientation(short norient);
    virtual void			setName(const std::string& name);
    virtual void			setCollide(bool ncollide);
    virtual world::World		*getWorld();
    virtual std::pair<double, double> const &	getPos() const;
    virtual std::pair<double, double> const &	getSize() const;
    virtual short			getOrientation() const;
    virtual int				getId() const;
    virtual bool			getCollide() const;
    virtual const std::string&		getName() const;
    virtual ABody			*clone(int id) const = 0;
    std::pair<double, double>		pointInFront(double dist);
    virtual unsigned int		getEntityId() const;
    virtual unsigned int		getTextureId() const;
    virtual unsigned int		getMeshId() const;
    virtual void			setTextureId();
    virtual void			setTextureId(int text);
    virtual void			setMeshId(int model);
    virtual void            setCooldown(unsigned long _cooldown);
    virtual void            setIdle(animations::AnimationsListJson);
    virtual void            setRunning(animations::AnimationsListJson);
  };

};

#endif
