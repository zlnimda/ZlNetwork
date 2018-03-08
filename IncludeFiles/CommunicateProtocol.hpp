#include	<iostream>
#include	"ZlNetwork.hpp"
#include	"ZRP.hpp"

#define		MAGIC	int(0x1234)
#define		IDENT	int(0x6543)
#define		TXT		int(0x1111)

class CommunicateProtocol : protected ZlNetwork::Handler::SocketHandler
{
protected:

  CommunicateProtocol() {}

  // PROTOCOL Bonjour : int MAGIC , string Pseudo
  void SendBonjour(ZlNetwork::Handler::SocketService Stream, const std::string & Pseudo)
  {
	Send(Stream, MAGIC, Pseudo);
  }

  template <typename T>
  void LisBonjour(T &obj, void (T::*fct) (ZlNetwork::Handler::SocketService, std::string))
  {
    typedef ZlNetwork::Handler::Function<void (T::*) (ZlNetwork::Handler::SocketService, std::string)> CallBack;

	CallBack *callback;
	ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener((callback = new CallBack(obj, fct)), std::get<0>(callback->params));
    (*l)(new ZlNetwork::Handler::Checker<int>(MAGIC))
		(new ZlNetwork::Handler::Catcher<std::string>(std::get<1>(callback->params)));
    addListener("Bonjour", l);
  }
  // PROTOCOL Bonjour [END]


  // PROTOCOL Identified : int IDENT
  void SendIdentified(ZlNetwork::Handler::SocketService Stream)
  {
	  Send(Stream, IDENT);
  }

  template <typename T>
  void LisIdentified(T &obj, void (T::*fct) (ZlNetwork::Handler::SocketService))
  {
    typedef ZlNetwork::Handler::Function<void (T::*) (ZlNetwork::Handler::SocketService)> CallBack;

	CallBack *callback;
	ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener((callback = new CallBack(obj, fct)), std::get<0>(callback->params));
    (*l)(new ZlNetwork::Handler::Checker<int>(IDENT));
    addListener("Identified", l);
  }
  // PROTOCOL Bonjour [END]


  // PROTOCOL TextMsg : int TXT, string Pseudo, string Msg
  void SendTxtMsg(ZlNetwork::Handler::SocketService Stream, const std::string & Pseudo, const std::string & Msg)
  {
	Send(Stream, TXT, Pseudo, Msg);
  }



  template <typename T>
  void LisTxtMsg(T &obj, void (T::*fct) (ZlNetwork::Handler::SocketService, std::string, std::string))
  {
    typedef ZlNetwork::Handler::Function<void (T::*) (ZlNetwork::Handler::SocketService, std::string, std::string)> CallBack;

	CallBack *callback;
	ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener((callback = new CallBack(obj, fct)), std::get<0>(callback->params));
    (*l)(new ZlNetwork::Handler::Checker<int>(TXT))
		(new ZlNetwork::Handler::Catcher<std::string>(std::get<1>(callback->params)))
		(new ZlNetwork::Handler::Catcher<std::string>(std::get<2>(callback->params)));
    addListener("TxtMsg", l);
  }
  // PROTOCOL TxtMsg [END]


private:
  CommunicateProtocol(const CommunicateProtocol & );
  const CommunicateProtocol & operator=(const CommunicateProtocol &);

};
