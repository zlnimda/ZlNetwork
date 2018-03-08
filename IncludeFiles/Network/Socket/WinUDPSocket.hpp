#ifndef		WINUDPSOCKET_H_
# define	WINUDPSOCKET_H_

#	include "IUDPSocket.hpp"
#	include "AWinSocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class WinUDPSocket :
      public IUDPSocket,
      public AWinSocket
    {
    public:
      WinUDPSocket(void);
      virtual ~WinUDPSocket(void);
	
      virtual bool Initialize(const std::string & address = std::string(), const std::string &port = std::string());

      virtual bool Send(Buffer::ISockBuffer &, Resolver::IAddrInfo &);

      virtual bool Receive(Buffer::ISockBuffer &, Resolver::IAddrInfo &);

    };
  }
}

#endif		// !WINUDPSOCKET_H_
