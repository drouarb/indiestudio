#ifndef  CORELISTENERDELETEPARTICLE_HH_
# define CORELISTENERDELETEPARTICLE_HH_

# include "PacketDeleteParticleListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerDeleteParticle : public network::PacketDeleteParticleListener
    {
    public:
      ListenerDeleteParticle(Core &);
      ~ListenerDeleteParticle();

      void			notify(const network::PacketDeleteParticle * packet);

    private:
      Core &			core;
    };
  };
};

#endif
