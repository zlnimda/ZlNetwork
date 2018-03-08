#ifndef		UNIXTCPSOCKET_H_
# define	UNIXTCPSOCKET_H_

#	include "ITCPSocket.hpp"
#	include	"AUnixSocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class UnixTCPSocket :
      public ITCPSocket,
      private AUnixSocket
    {
    public:
      UnixTCPSocket(void);
      virtual ~UnixTCPSocket(void);

      virtual bool Initialize(const std::string & address = std::string(), const std::string &port = std::string());

      virtual bool Listen(int backlog);

      virtual ITCPSocket * accept();

      virtual bool Connect(const std::string & address, const std::string & port);

      virtual bool Send(Buffer::ISockBuffer &);

      virtual bool Receive(Buffer::ISockBuffer &);
	
      virtual bool IsConnected() const;

      virtual Resolver::IAddrInfo * GetConnectionInfo() const;

      virtual void Close();

    private:
      UnixTCPSocket(int, Resolver::IAddrInfo *);

      bool			_isConnected;
      Resolver::IAddrInfo *	_addrInfo;
    };
  }
}

#endif		// !UNIXTCPSOCKET_H_
