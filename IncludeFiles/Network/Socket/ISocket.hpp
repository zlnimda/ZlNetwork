#ifndef		ISOCKET_H_
# define	ISOCKET_H_

# include <string>
# include <stdlib.h>
# include "ISockBuffer.hpp"
# include "IAddrInfo.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class ISocket
    {
    public:
      virtual ~ISocket(void) { }

      virtual bool Initialize(int family, int type, int protocol, const std::string & address = std::string(), const std::string &port = std::string()) = 0;

      virtual void Close() = 0;
	
      virtual bool Poll(bool & read, bool & write) = 0;

      virtual bool IsValid() const = 0;

    private:
      virtual bool Bind(Resolver::IAddrInfo & ) = 0;
    };
  }
}

#endif		// !ISOCKET_H_
