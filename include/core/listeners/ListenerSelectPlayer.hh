#ifndef  CORELISTENERSELECTPLAYER_HH_
# define CORELISTENERSELECTPLAYER_HH_

# include "PacketSelectPlayerListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerSelectPlayer : public network::PacketSelectPlayerListener
    {
    public:
      ListenerSelectPlayer(Core &);
      ~ListenerSelectPlayer();

      void			notify(const network::PacketSelectPlayer * packet);

    private:
      Core &			core;
    };
  };
};

#endif
