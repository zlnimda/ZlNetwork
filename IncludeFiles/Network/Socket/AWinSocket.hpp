#ifndef		AWINSOCKET_H_
# define	AWINSOCKET_H_

# include <Ws2tcpip.h>
# include <Winsock2.h>
# include "ISocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class AWinSocket :
      virtual public ISocket
    {
    protected:
      SOCKET _socket;
	
    public:
      AWinSocket(void);
      virtual ~AWinSocket(void);

      virtual bool Initialize(int family, int type, int protocol, const std::string & address = std::string(), const std::string &port = std::string());

      virtual void Close();
	
      virtual bool Poll(bool & read, bool & write);

      virtual bool IsValid() const;

    private:
      virtual bool Bind(Resolver::IAddrInfo & csin);
    };
  }
}

#endif		// !AWINSOCKET_H_
