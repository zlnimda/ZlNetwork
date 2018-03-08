#ifndef		AUNIXSOCKET_H_
# define	AUNIXSOCKET_H_

# include "ISocket.hpp"

namespace ZlNetwork
{
  namespace Socket
  {
    class AUnixSocket :
      virtual public ISocket
    {
    protected:
      int _socket;

    public:
      AUnixSocket(void);
      virtual ~AUnixSocket(void);

      virtual bool Initialize(int family, int type, int protocol, const std::string & address = std::string(), const std::string &port = std::string());

      virtual void Close();

      virtual bool Poll(bool & read, bool & write);

      virtual bool IsValid() const;

    private:
      virtual bool Bind(Resolver::IAddrInfo & csin);
    };
  }
}

#endif		// !AUNIXSOCKET_H_
