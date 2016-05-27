#ifndef  CORELISTENERPLAYSOUND_HH_
# define CORELISTENERPLAYSOUND_HH_

# include "PacketPlaySoundListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerPlaySound : public network::PacketPlaySoundListener
    {
    public:
      ListenerPlaySound(Core &);
      ~ListenerPlaySound();

      void			notify(const network::PacketPlaySound * packet);

    private:
      Core &			core;
    };
  };
};

#endif
