#ifndef		ZRP_HPP_
# define	ZRP_HPP_

#include	"ZlNetwork.hpp"

namespace ZlNetwork
{
  class		ZRP : public Handler::SocketHandler
  {
  public:
    ZRP()
    {
    }


    /********************************************************/
    /*********************** LISTENER ***********************/
    /********************************************************/


    /** Connection Server **/

    template <class C>
    void addConnectionServer(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(21))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<short>(0xabe));
      addListener("ConnectionServer", l);
    }

    template <class C>
    void addConnected(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(41))
	(new ZlNetwork::Handler::Checker<char>(0));
      addListener("Connected", l);
    }


    /** List Games **/

    template <class C>
    void addListGames(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(22))
	(new ZlNetwork::Handler::Checker<char>(0));
      addListener("ListGames", l);
    }

    template <class C>
    void addGames(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, std::list<std::string>, std::list<char>))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, std::list<std::string>, std::list<char>);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(42))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(5))
	(new ZlNetwork::Handler::Checker<char>(5))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Catcher<std::list<std::string> >(ZlNetwork::Handler::Function<F>::_2))
	(new ZlNetwork::Handler::Catcher<std::list<char> >(ZlNetwork::Handler::Function<F>::_3));
      addListener("Games", l);
    }


    /** Start Game **/

    template <class C>
    void addStartGame(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, std::string))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, std::string);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(23))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Catcher<std::string>(ZlNetwork::Handler::Function<F>::_2));
      addListener("StartGame", l);
    }

    template <class C>
    void addStarted(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, unsigned short))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, unsigned short);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(43))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(3))
	(new ZlNetwork::Handler::Catcher<unsigned short>(ZlNetwork::Handler::Function<F>::_2));
      addListener("Started", l);
    }

    template <class C>
    void addFull(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(44))
	(new ZlNetwork::Handler::Checker<char>(0));
      addListener("Full", l);
    }

		template <class C>
    void addGivePort(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, unsigned short))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, unsigned short);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(50))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(3))
	(new ZlNetwork::Handler::Catcher<unsigned short>(ZlNetwork::Handler::Function<F>::_2));
      addListener("GivePort", l);
    }


    /** Connection Player **/

    template <class C>
    void addConnectionPlayer(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, std::string))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, std::string);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(24))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Catcher<std::string>(ZlNetwork::Handler::Function<F>::_2));
      addListener("ConnectionPlayer", l);
    }


    /** Disconnection Player **/

    template <class C>
    void addDisconnectionPlayer(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, std::string))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, std::string);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(25))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Catcher<std::string>(ZlNetwork::Handler::Function<F>::_2));
      addListener("DisconnectionPlayer", l);
    }
    

    /** Controls **/

    template <class C>
    void addControls(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, float, float, char))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, float, float, char);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(31))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_2))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_3))
  (new ZlNetwork::Handler::Catcher<char>(ZlNetwork::Handler::Function<F>::_4));
      addListener("Controls", l);
    }
      

    /** Creation Sprite **/

    template <class C>
    void addCreationSprite(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, short, char))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, short, char);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(32))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(2))
  (new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Catcher<short>(ZlNetwork::Handler::Function<F>::_2))
  (new ZlNetwork::Handler::Catcher<char>(ZlNetwork::Handler::Function<F>::_3));
      addListener("CreationSprite", l);
    }
    

    /** Destruction Sprite **/

    template <class C>
    void addDestructionSprite(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, short))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, short);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(33))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Catcher<short>(ZlNetwork::Handler::Function<F>::_2));
      addListener("DestructionSprite", l);
    }
    

    /** Data Sprite **/

    template <class C>
    void addDataSprite(C &obj, void (C::*fct)(ZlNetwork::Handler::SocketService, short, float, float, float, float, float, float))
    {
      typedef void (C::*F)(ZlNetwork::Handler::SocketService, short, float, float, float, float, float, float);
      ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener(new ZlNetwork::Handler::Function<F>(obj, fct),
									  ZlNetwork::Handler::Function<F>::_1);
      (*l)(new ZlNetwork::Handler::Checker<char>(34))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<char>(2))
  (new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(6))
	(new ZlNetwork::Handler::Catcher<short>(ZlNetwork::Handler::Function<F>::_2))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_3))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_4))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_5))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_6))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_7))
  (new ZlNetwork::Handler::Catcher<float>(ZlNetwork::Handler::Function<F>::_8));
      addListener("DataSprite", l);
    }

    /********************************************************/
    /************************ SENDER ************************/
    /********************************************************/


    /** Connection Server **/

    void sendConnectionServer(ZlNetwork::Handler::SocketService _1)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(21))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<short>(0xabe));
      AddSender(_1, s);
    }

    void sendConnected(ZlNetwork::Handler::SocketService _1)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(41))
	(new ZlNetwork::Handler::Checker<char>(0));
      AddSender(_1, s);
    }


    /** List Games **/

    void sendListGames(ZlNetwork::Handler::SocketService _1)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(22))
	(new ZlNetwork::Handler::Checker<char>(0));
      AddSender(_1, s);
    }

    void sendGames(ZlNetwork::Handler::SocketService _1, std::list<std::string> & _2, std::list<char> & _3)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(42))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(5))
	(new ZlNetwork::Handler::Checker<char>(5))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<std::list<std::string> >(_2))
	(new ZlNetwork::Handler::Checker<std::list<char> >(_3));
      AddSender(_1, s);
    }


    /** Start Game **/

    void sendStartGame(ZlNetwork::Handler::SocketService _1, std::string const & _2)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(23))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<std::string>(_2));
      AddSender(_1, s);
    }

    void sendStarted(ZlNetwork::Handler::SocketService _1, unsigned short _2)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(43))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(3))
	(new ZlNetwork::Handler::Checker<unsigned short>(_2));
      AddSender(_1, s);
    }

    void sendFull(ZlNetwork::Handler::SocketService _1)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(44))
	(new ZlNetwork::Handler::Checker<char>(0));
      AddSender(_1, s);
    }

    void sendGivePort(ZlNetwork::Handler::SocketService _1, unsigned short _2)
    {
     ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(50))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(3))
	(new ZlNetwork::Handler::Checker<unsigned short>(_2));
      AddSender(_1, s);
    }

    /** Connection Player **/

    void sendConnectionPlayer(ZlNetwork::Handler::SocketService _1, std::string & _2)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(24))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<std::string>(_2));
      AddSender(_1, s);
    }


    /** Disconnection Player **/

    void sendDisconnectionPlayer(ZlNetwork::Handler::SocketService _1, std::string & _2)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(25))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<std::string>(_2));
      AddSender(_1, s);
    }
    

    /** Controls **/

    void sendControls(ZlNetwork::Handler::SocketService _1, float _2, float _3, char _4)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(31))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<float>(_2))
  (new ZlNetwork::Handler::Checker<float>(_3))
  (new ZlNetwork::Handler::Checker<char>(_4));
      AddSender(_1, s);
    }
      

    /** Creation Sprite **/

    void sendCreationSprite(ZlNetwork::Handler::SocketService _1, short _2, char _3)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(32))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<char>(2))
  (new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<short>(_2))
  (new ZlNetwork::Handler::Checker<char>(_3));
      AddSender(_1, s);
    }
    

    /** Destruction Sprite **/

    void sendDestructionSprite(ZlNetwork::Handler::SocketService _1, short _2)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(33))
	(new ZlNetwork::Handler::Checker<char>(1))
	(new ZlNetwork::Handler::Checker<char>(2))
	(new ZlNetwork::Handler::Checker<short>(_2));
      AddSender(_1, s);
    }
    

    /** Data Sprite **/

    void sendDataSprite(ZlNetwork::Handler::SocketService _1, short _2, float _3, float _4, float _5, float _6, float _7, float _8)
    {
      ZlNetwork::Handler::Sender * s = new ZlNetwork::Handler::Sender();
      (*s)(new ZlNetwork::Handler::Checker<char>(34))
	(new ZlNetwork::Handler::Checker<char>(4))
	(new ZlNetwork::Handler::Checker<char>(2))
  (new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(6))
  (new ZlNetwork::Handler::Checker<char>(6))
	(new ZlNetwork::Handler::Checker<short>(_2))
  (new ZlNetwork::Handler::Checker<float>(_3))
  (new ZlNetwork::Handler::Checker<float>(_4))
  (new ZlNetwork::Handler::Checker<float>(_5))
  (new ZlNetwork::Handler::Checker<float>(_6))
  (new ZlNetwork::Handler::Checker<float>(_7))
  (new ZlNetwork::Handler::Checker<float>(_8));
      AddSender(_1, s);
    }


  };
}

#endif		//!ZRP_HPP_
