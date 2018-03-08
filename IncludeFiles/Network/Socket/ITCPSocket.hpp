#ifndef		ITCPSOCKET_H_
# define	ITCPSOCKET_H_

# include "ISocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class ITCPSocket :
      virtual public ISocket
    {
    public:
      virtual ~ITCPSocket(void) { }

      virtual bool Initialize(const std::string & address = std::string(), const std::string &port = std::string()) = 0;

      virtual bool Listen(int backlog) = 0;

      virtual ITCPSocket * accept() = 0;

      virtual bool Connect(const std::string & address, const std::string & port) = 0;

      virtual bool Send(Buffer::ISockBuffer &) = 0;

      virtual bool Receive(Buffer::ISockBuffer &) = 0;

      virtual bool IsConnected() const = 0;

      virtual Resolver::IAddrInfo * GetConnectionInfo() const = 0;

    };

    ITCPSocket * CreateTCPSocket();
  }
}

#endif		// !ITCPSOCKET_H_
