#ifndef		UNIXADDRINFO_H_
# define	UNIXADDRINFO_H_

# include "IAddrInfo.hpp"

namespace ZlNetwork
{
  namespace Resolver
  {
    class UnixAddrInfo :
      public IAddrInfo
    {
      struct addrinfo *	_result;
      bool			_wasCreated;

    public:
      UnixAddrInfo(const std::string & node, const std::string & service, int socktype, int protocol, int family = AF_UNSPEC);
      UnixAddrInfo();
      virtual ~UnixAddrInfo(void);

      virtual struct addrinfo * GetResult(void) const;
	  
	  virtual std::string GetIp() const;
      
      virtual std::string GetPort() const;

      virtual bool SameAs(IAddrInfo *) const;

    private:
      UnixAddrInfo(UnixAddrInfo &);
    };
  }
}

#endif		// !UNIXADDRINFO_H_
