#ifndef		ZL_SOCKETHANDLER_HPP_
# define	ZL_SOCKETHANDLER_HPP_

# include	<iostream>
# include	<map>
# include	<list>
# include	"Function.hpp"
# include	"ITCPSocket.hpp"
# include	"IUDPSocket.hpp"
# include	"Listener.hpp"

namespace ZlNetwork
{
  namespace Handler
  {

    class SocketHandler
    {
    public:
      SocketHandler();
      virtual ~SocketHandler();

      template <typename T>
      SocketService	CreateServerTCPSocket(T & obj, void (T::*fct)(SocketService), const std::string & port, const std::string & addr = std::string("0.0.0.0"), int backlog = 5)
      {
	SocketService serv = CreateTCPSocket();
	_map[serv]->stcp->Initialize(addr, port);
	_map[serv]->stcp->Listen(backlog);
	Function<void (T::*)(SocketService)> *function = new Function<void (T::*)(SocketService)>(obj, fct);
	_map[serv]->accept = function;
	_map[serv]->_1_accept = &std::get<0>(function->params);
	_map[serv]->server = true;
	return serv;
      }

      SocketService	CreateClientTCPSocket(const std::string & addr, const std::string & port);

      SocketService	CreateUDPSocket(const std::string & port, const std::string & addr = std::string("0.0.0.0"));

      SocketService	CreateUDPSocket();

      void		AddListener(SocketService s, const std::string & name);
      void		DisableListener(SocketService s, const std::string & name);
      void		EnableListener(SocketService s, const std::string & name);
      void		SetEnablenessListener(SocketService s, const std::string & name, bool value);

      void		AddSender(SocketService s, Sender *sender);

      bool		IsValid(SocketService s);

      virtual void	Update(); // IMPORTANT

      static SocketService FailSocket;


      // Get Ip From Last connection
      std::string GetIp(SocketService);

      // Get Resolver From Last connection
      Resolver::IAddrInfo * getLastFromUdp(SocketService);

      // Add Client to a UDP Socket Service to send multiple message
      void  addResolverId(SocketService s, Resolver::IAddrInfo *);
      void  removeResolverId(SocketService s, Resolver::IAddrInfo *);

	  /// TEMPLATE Sending

	private:
		template <typename ...ARGS> void SendCallArg(ZlNetwork::Handler::SocketService Stream, ZlNetwork::Handler::Sender *Sender, ARGS...);

		template <typename ARG, typename ...ARGS> void SendCallArg(ZlNetwork::Handler::SocketService Stream, ZlNetwork::Handler::Sender *Sender, ARG arg, ARGS... args)
		{
			(*Sender)(new ZlNetwork::Handler::Checker<ARG>(arg));
			SendCallArg(Stream, Sender, args...);
		}

		template <typename ARG> void SendCallArg(ZlNetwork::Handler::SocketService Stream, ZlNetwork::Handler::Sender *Sender, ARG arg)
		{
			(*Sender)(new ZlNetwork::Handler::Checker<ARG>(arg));
			AddSender(Stream, Sender);
		}

	public:
	  template <typename ...ARGS> void Send(ZlNetwork::Handler::SocketService Stream, ARGS... args)
	  {
		  ZlNetwork::Handler::Sender *Sender = new ZlNetwork::Handler::Sender();
		  SendCallArg(Stream, Sender, args...);
	  }


	  //// END TEMPLATE

	  /// TEMPLATE Add Listener

	private:
		template <typename P_FCT, typename CallBack = ZlNetwork::Handler::Function<P_FCT>, typename ...ARGS>
		void AddListenerCallArg(CallBack *callback, ZlNetwork::Handler::Listener * l, ARGS... args);


		template <typename P_FCT, typename CallBack = ZlNetwork::Handler::Function<P_FCT>, typename ...ARGS>
		void AddListenerCallArg<P_FCT, CallBack, std::string, ARGS...>(CallBack *callback, ZlNetwork::Handler::Listener * l, std::string arg, ARGS... args)
		{
			(*l)(new ZlNetwork::Handler::Catcher(std::get<0>(callback->params)));
			AddListenerCallArg(callback, l, args...);
		}

		template <typename P_FCT, typename CallBack = ZlNetwork::Handler::Function<P_FCT>, typename ARG, typename ...ARGS>
		void AddListenerCallArg(CallBack *callback, ZlNetwork::Handler::Listener * l, ARG arg, ARGS... args)
		{
			(*l)(new ZlNetwork::Handler::Checker<ARG>(arg));
			AddListenerCallArg(callback, l, args...);
		}

		template <typename P_FCT, typename CallBack = ZlNetwork::Handler::Function<P_FCT>, typename ARG>
		void AddListenerCallArg(CallBack *callback, ZlNetwork::Handler::Listener * l, ARG arg)
		{
			(*l)(new ZlNetwork::Handler::Checker<ARG>(arg));
		}



	public:
	  template <typename T, typename ...O_ARGS, typename P_FCT = void (T::*)(ZlNetwork::Handler::SocketService, O_ARGS...), typename CallBack = ZlNetwork::Handler::Function<P_FCT>, typename ...ARGS>
	  void AddListener(std::string name, T &obj, P_FCT fct , ARGS... args)
	  {
		  CallBack *callback;
		  ZlNetwork::Handler::Listener * l = new ZlNetwork::Handler::Listener((callback = new CallBack(obj, fct)), std::get<0>(callback->params));
		  AddListenerCallArg(callback, l, args...);
		  addListener(name, l);
	  }

	  //// END TEMPLATE

	protected:
      void		addListener(const std::string &, Listener *listener);

    private:
      SocketHandler(const SocketHandler &);
      const SocketHandler & operator=(const SocketHandler &);

      SocketService	AddTCPService(Socket::ITCPSocket *);
      SocketService	AddUDPService(Socket::IUDPSocket *);

      SocketService	CreateTCPSocket();

      bool	UpdateTCP(SocketService);
      void	UpdateTCPRead(SocketService);
      void	UpdateTCPWrite(SocketService);

      bool	UpdateUDP(SocketService);
      void	UpdateUDPRead(SocketService);
      void	UpdateUDPWrite(SocketService);

      static SocketService counter;

      struct Service
      {
	Service();
	~Service();
	bool tcp;
	bool server;
	union
	{
	  Socket::IUDPSocket * sudp;
	  Socket::ITCPSocket * stcp;
	};
	IFunction * accept;
	SocketService * _1_accept;
	std::map<std::string, bool> rules;
	std::list<Sender *> _sender;
	Resolver::IAddrInfo *addr;
	std::list<Resolver::IAddrInfo *> listUdp;
      };
      std::map<std::string, Listener *> _listener;
      std::map<SocketService, Service *> _map;
      Buffer::AdvSockBuffer _buff;
    };
  }
}

#endif		//! ZL_SOCKETHANDLER_HPP_
