#ifndef  CORELISTENERADDENTITY_HH_
# define CORELISTENERADDENTITY_HH_

# include "PacketAddEntityListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerAddEntity : public network::PacketAddEntityListener
    {
    public:
      ListenerAddEntity(Core &);
      ~ListenerAddEntity();

      void			notify(const network::PacketAddEntity * packet);

    private:
      Core &			core;
    };
  };
};

#endif
