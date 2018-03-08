#ifndef		WINADDRINFO_H_
# define	WINADDRINFO_H_

# include "IAddrInfo.hpp"

namespace ZlNetwork
{
  namespace Resolver
  {
    class WinAddrInfo :
      public IAddrInfo
    {
      struct addrinfo * _result;
      bool							_wasCreated;

    public:
      WinAddrInfo(const std::string & node, const std::string & service, int socktype, int protocol, int family = AF_UNSPEC);
      WinAddrInfo();
      virtual ~WinAddrInfo(void);

      virtual struct addrinfo * GetResult(void) const;

      virtual std::string GetIp() const;
      
      virtual std::string GetPort() const;

      virtual bool SameAs(IAddrInfo *) const;

    private:
      WinAddrInfo(WinAddrInfo &);
      WinAddrInfo const & operator=(WinAddrInfo const &);
    };
  }
}

#endif		// !WINADDRINFO_H_
