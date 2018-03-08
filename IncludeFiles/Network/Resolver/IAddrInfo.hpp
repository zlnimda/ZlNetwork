#ifndef		IADDRINFO_H_
# define	IADDRINFO_H_

# include	<string>
# ifdef		_WIN32
#  include	<Winsock2.h>
#  include	<Ws2tcpip.h>
# else
#  include <arpa/inet.h>
#  include	<sys/types.h>
#  include	<sys/socket.h>
#  include	<netdb.h>
# endif

namespace ZlNetwork
{
  namespace Resolver
  {
    class IAddrInfo
    {
    public:
      IAddrInfo(const std::string & node, const std::string & service, int socktype, int protocol, int family = AF_UNSPEC) { }
      virtual ~IAddrInfo(void) { }

      virtual struct addrinfo * GetResult(void) const = 0;

      virtual std::string GetIp() const = 0;
      
      virtual std::string GetPort() const = 0;

      virtual bool SameAs(IAddrInfo *) const = 0;

    protected:
      IAddrInfo(void) { }

    private:
      IAddrInfo(IAddrInfo &);
      const IAddrInfo & operator=(const IAddrInfo &);
    };

    IAddrInfo * CreateAddrInfo(const std::string & node, const std::string & service, int socktype = SOCK_STREAM, int protocol = IPPROTO_TCP, int family = AF_INET);
    IAddrInfo * CreateAddrInfo();
  }
}

#endif		// !IADDRINFO_H_
