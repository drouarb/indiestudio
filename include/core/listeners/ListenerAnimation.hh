#ifndef  CORELISTENERANIMATION_HH_
# define CORELISTENERANIMATION_HH_

# include "PacketAnimationListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerAnimation : public network::PacketAnimationListener
    {
    public:
      ListenerAnimation(Core &);
      ~ListenerAnimation();

      void			notify(const network::PacketAnimation * packet);

    private:
      Core &			core;
    };
  };
};

#endif
