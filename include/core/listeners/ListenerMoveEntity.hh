#ifndef  CORELISTENERMOVEENTITY_HH_
# define CORELISTENERMOVEENTITY_HH_

# include "PacketMoveEntityListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerMoveEntity : public network::PacketMoveEntityListener
    {
    public:
      ListenerMoveEntity(Core &);
      ~ListenerMoveEntity();

      void			notify(const network::PacketMoveEntity * packet);

    private:
      Core &			core;
    };
  };
};

#endif
