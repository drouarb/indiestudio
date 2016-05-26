#ifndef  ACTIONLISTS_HH_
# define ACTIONLISTS_HH_

# include <list>
# include "ListenerAddEntity.hh"
# include "ListenerDisconnect.hh"
# include "ListenerMoveEntity.hh"
# include "ListenerDeleteEntity.hh"
# include "ListenerStopSound.hh"
# include "ListenerPlaySound.hh"
# include "ListenerAddParticle.hh"
# include "ListenerDeleteParticle.hh"

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
      void			pushMoveEntity(const network::PacketMoveEntity *);
      void			pushDeleteEntity(const network::PacketDeleteEntity *);
      void			pushStopSound(const network::PacketStopSound *);
      void			pushPlaySound(const network::PacketPlaySound *);
      void			pushAddParticle(const network::PacketAddParticle *);
      void			pushDeleteParticle(const network::PacketDeleteParticle *);
      void			setCameraTrackerId(int id);

    private:
      Core &			core;

      void			clearActions();

      bool			pendingTracker;
      int			entityIdTracker;

      std::list<network::Packet*> allPackets;
      std::list<network::PacketAddEntity*> packetsAddEntity;
      std::list<network::PacketDisconnect*> packetsDisconnect;
      std::list<network::PacketMoveEntity*> packetsMoveEntity;
      std::list<network::PacketDeleteEntity*> packetsDeleteEntity;
      std::list<network::PacketStopSound*> packetsStopSound;
      std::list<network::PacketPlaySound*> packetsPlaySound;
      std::list<network::PacketAddParticle*> packetsAddParticle;
      std::list<network::PacketDeleteParticle*> packetsDeleteParticle;
    };
  };
};

#endif
