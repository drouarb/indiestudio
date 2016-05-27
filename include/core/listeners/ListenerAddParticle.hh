#ifndef  CORELISTENERADDPARTICLE_HH_
# define CORELISTENERADDPARTICLE_HH_

# include "PacketAddParticleListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerAddParticle : public network::PacketAddParticleListener
    {
    public:
      ListenerAddParticle(Core &);
      ~ListenerAddParticle();

      void			notify(const network::PacketAddParticle * packet);

    private:
      Core &			core;
    };
  };
};

#endif
