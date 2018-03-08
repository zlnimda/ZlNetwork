#ifndef		WINTCPSOCKET_H_
# define	WINTCPSOCKET_H_

# include "ITCPSocket.hpp"
# include "AWinSocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class WinTCPSocket :
      public ITCPSocket,
      public AWinSocket
    {
    public:
      WinTCPSocket(void);
      virtual ~WinTCPSocket(void);

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
      WinTCPSocket(SOCKET, Resolver::IAddrInfo *);

      bool				_isConnected;
      Resolver::IAddrInfo *	_addrInfo;
    };
  }
}

#endif		// !WINTCPSOCKET_H_
