#ifndef		WINSOCKBUFFER_H_
# define	WINSOCKBUFFER_H_

# include <Winsock2.h>
# include "ISockBuffer.hpp"

namespace ZlNetwork
{
  namespace Buffer
  {
    typedef ULONG	SOCKBUFF_ULONG;

    struct ISockBuffer::SockBuffer : WSABUF { };

    class WinSockBuffer :
      public ISockBuffer
    {
    public:

      WinSockBuffer(void);
      virtual ~WinSockBuffer(void);

      template<typename T>
      void SetBuffer(T * buffer, ULONG length)
      {
	union {
	  CHAR *cptr;
	  T * tptr;
	} tmp;
	tmp.tptr = buffer;
	_buff.buf = tmp.cptr;
	_buff.len = length;
      }

      virtual struct ISockBuffer::SockBuffer * GetLpBuffer(void);

    private:
      struct ISockBuffer::SockBuffer	_buff;
    };

    template <typename T>
    void _SetBuffer(ISockBuffer * sockBuffer, T *buffer, SOCKBUFF_ULONG length)
    {
      WinSockBuffer * wsockbuffer = dynamic_cast<WinSockBuffer *>(sockBuffer);
      if (wsockbuffer)
	wsockbuffer->SetBuffer<T>(buffer, length);
    }
  }
}

#endif		// !WINSOCKBUFFER_H_
