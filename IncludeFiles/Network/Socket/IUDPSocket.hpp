#ifndef		IUDPSOCKET_H_
# define	IUDPSOCKET_H_

# include "ISocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class IUDPSocket :
      virtual public ISocket
    {
    public:
      virtual ~IUDPSocket(void) { }
	
      virtual bool Initialize(const std::string & address = std::string(), const std::string &port = std::string()) = 0;

      virtual bool Send(Buffer::ISockBuffer &, Resolver::IAddrInfo &) = 0;

      virtual bool Receive(Buffer::ISockBuffer &, Resolver::IAddrInfo &) = 0;

    };

    IUDPSocket * CreateUDPSocket();
  }
}

#endif		// !IUDPSOCKET_H_
