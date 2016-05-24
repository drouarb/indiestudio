#ifndef  CORELISTENERDELETEENTITY_HH_
# define CORELISTENERDELETEENTITY_HH_

# include "PacketDeleteEntityListener.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			ListenerDeleteEntity : public network::PacketDeleteEntityListener
    {
    public:
      ListenerDeleteEntity(Core &);
      ~ListenerDeleteEntity();

      void			notify(const network::PacketDeleteEntity * packet);

    private:
      Core &			core;
    };
  };
};

#endif
