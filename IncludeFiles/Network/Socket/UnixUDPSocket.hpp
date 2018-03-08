#ifndef		UNIXUDPSOCKET_H_
# define	UNIXUDPSOCKET_H_

# include "IUDPSocket.hpp"
# include "AUnixSocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class UnixUDPSocket :
      public IUDPSocket,
      public AUnixSocket
    {
    public:
      UnixUDPSocket(void);
      virtual ~UnixUDPSocket(void);
	
      virtual bool Initialize(const std::string & address = std::string(), const std::string &port = std::string());

      virtual bool Send(Buffer::ISockBuffer &, Resolver::IAddrInfo &);

      virtual bool Receive(Buffer::ISockBuffer &, Resolver::IAddrInfo &);

    };
  }
}

#endif		// !UNIXUDPSOCKET_H_
