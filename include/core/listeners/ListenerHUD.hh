#ifndef  CORELISTENERHUD_HH_
# define CORELISTENERHUD_HH_

# include "PacketHUDListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerHUD : public network::PacketHUDListener
    {
    public:
      ListenerHUD(Core &);
      ~ListenerHUD();

      void			notify(const network::PacketHUD * packet);

    private:
      Core &			core;
    };
  };
};

#endif
