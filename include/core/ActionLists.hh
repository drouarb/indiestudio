#ifndef  ACTIONLISTS_HH_
# define ACTIONLISTS_HH_

# include <list>
# include "ListenerAddEntity.hh"
# include "ListenerDisconnect.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ActionLists
    {
    public:
      ActionLists(Core &);
      ~ActionLists();

      void			doActions();
      void			pushAddEntity(const network::PacketAddEntity *);
      void			pushDisconnect(const network::PacketDisconnect *);

    private:
      Core &			core;

      void			clearActions();

      std::list<network::PacketAddEntity*> packetsAddEntity;
      std::list<network::PacketDisconnect*> packetsDisconnect;
    };
  };
};

#endif
