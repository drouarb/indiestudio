#ifndef  CORELISTENERDISCONNECT_HH_
# define CORELISTENERDISCONNECT_HH_

# include "PacketDisconnectListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerDisconnect : public network::PacketDisconnectListener
    {
    public:
      ListenerDisconnect(Core &);
      ~ListenerDisconnect();

      void			notify(const network::PacketDisconnect * packet);

    private:
      Core &			core;
    };
  };
};

#endif
