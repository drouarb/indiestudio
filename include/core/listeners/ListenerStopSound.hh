#ifndef  CORELISTENERSTOPSOUND_HH_
# define CORELISTENERSTOPSOUND_HH_

# include "PacketStopSoundListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerStopSound : public network::PacketStopSoundListener
    {
    public:
      ListenerStopSound(Core &);
      ~ListenerStopSound();

      void			notify(const network::PacketStopSound * packet);

    private:
      Core &			core;
    };
  };
};

#endif
