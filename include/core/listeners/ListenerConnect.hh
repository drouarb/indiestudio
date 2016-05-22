#ifndef  CORELISTENERCONNECT_HH_
# define CORELISTENERCONNECT_HH_

# include "PacketConnectListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerConnect : public network::PacketConnectListener
    {
    public:
      ListenerConnect(Core &);
      ~ListenerConnect();

      void			notify(const network::PacketConnect * packet);

    private:
      Core &			core;
    };
  };
};

#endif
