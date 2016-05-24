#ifndef  WAITPACKET_HH_
# define WAITPACKET_HH_

# include <thread>
# include "Menu.hh"
# include "Packet.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			WaitPacket : public Menu
    {
    public:
      WaitPacket(Core &, int idStart, Menu * parent);
      ~WaitPacket();

      void			draw();
      void			undraw();
      bool			keyDown(Command);
      bool			receivedValue();

      static void		receive(network::Packet const * packet);
      static network::Packet const * getReceived();

    protected:
      void			doButton(int, struct t_hitItem &);
      void			timer();

      static bool		receivedSomething(bool set, bool val);
      static network::Packet const * packet(network::Packet const * packet, bool set);
      static bool		mustClose(bool set, bool val);
    };
  };
};

#endif
