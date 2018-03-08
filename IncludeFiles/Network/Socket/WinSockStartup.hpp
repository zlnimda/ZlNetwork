#ifndef		WINSOCKSTARTUP_H_
#	define	WINSOCKSTARTUP_H_

#	include <Winsock2.h>

namespace ZlNetwork
{
  namespace Socket
  {
    class WinSockStartup
    {
    public:
      static void Start(void);
    private:
      WinSockStartup(void);
      WinSockStartup(WinSockStartup &);
      WinSockStartup const & operator=(WinSockStartup const &);

      ~WinSockStartup(void);

      WSADATA	_wsaData;
    };
  }
}

#endif		// !WINSOCKSTARTUP_H_
