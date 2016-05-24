#ifndef  CORELISTENERSTARTGAME_HH_
# define CORELISTENERSTARTGAME_HH_

# include "PacketStartGameListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerStartGame : public network::PacketStartGameListener
    {
    public:
      ListenerStartGame(Core &);
      ~ListenerStartGame();

      void			notify(const network::PacketStartGame * packet);

    private:
      Core &			core;
    };
  };
};

#endif
