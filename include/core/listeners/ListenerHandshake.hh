#ifndef  CORELISTENERHANDSHAKE_HH_
# define CORELISTENERHANDSHAKE_HH_

# include "PacketHandshakeListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerHandshake : public network::PacketHandshakeListener
    {
    public:
      ListenerHandshake(Core &);
      ~ListenerHandshake();

      void			notify(const network::PacketHandshake * packet);

    private:
      Core &			core;
    };
  };
};

#endif
