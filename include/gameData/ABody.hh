//
// ABody.hh for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:06:15 2016 Alexis Trouve
// Last update Wed May 18 16:45:08 2016 Alexis Trouve
//

#ifndef ABODY_HH_
# define ABODY_HH_

#include <tuple>

namespace gauntlet
{
  class ABody
  {
  private:
    bool			collideActive;
    int				id;
    std::pair<double, double>	coord;
    std::pair<double, double>	size;
    short			orientation;
  public:
    ABody(bool collide, int nid, double posx,
	  double posy, double sizex, double sizey, short norient);
    ABody(int nid, double posx, double posy, double sizex,
	  double sizey, short norient);
    virtual ~ABody();

    virtual bool			isCollide(std::pair<double, double> checkpos,
						  std::pair<double, double> checksize);

    virtual void			changePos(double nposx, double nposy);
    virtual void			changeOrientation(short norient);
    virtual void			setCollide(bool ncollide);

    virtual std::pair<double, double> const &	getPos() const;
    virtual std::pair<double, double> const &	getSize() const;
    virtual short			getOrientation() const;
    virtual int				getId() const;
    virtual bool			getCollide() const;
  };
};

#endif
