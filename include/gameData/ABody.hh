//
// ABody.hh for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:06:15 2016 Alexis Trouve
// Last update Fri May 20 14:19:26 2016 Alexis Trouve
//

#ifndef ABODY_HH_
# define ABODY_HH_

#include "Math.hh"
#include <tuple>

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
  public:
    ABody(int nid);
    virtual ~ABody();

    virtual void			changePos(const std::pair<double, double>& ncoord);
    virtual void			changeSize(const std::pair<double, double>& nsize);
    virtual void			changeOrientation(short norient);
    virtual void			setName(const std::string& name);
    virtual void			setCollide(bool ncollide);
    virtual world::World    *getWorld();
    virtual std::pair<double, double> const &	getPos() const;
    virtual std::pair<double, double> const &	getSize() const;
    virtual short			getOrientation() const;
    virtual int				getId() const;
    virtual bool			getCollide() const;
    virtual const std::string&		getName() const;
    virtual ABody			*clone(int id) const = 0;
    std::pair<double, double> pointInFront(double dist);
  };

};

#endif
