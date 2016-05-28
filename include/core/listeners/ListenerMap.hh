#ifndef  CORELISTENERMAP_HH_
# define CORELISTENERMAP_HH_

# include "PacketMapListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerMap : public network::PacketMapListener
    {
    public:
      ListenerMap(Core &);
      ~ListenerMap();

      void			notify(const network::PacketMap * packet);

    private:
      Core &			core;
    };
  };
};

#endif
