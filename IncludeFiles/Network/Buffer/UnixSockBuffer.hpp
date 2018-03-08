#ifndef		UNIXSOCKBUFFER_H_
# define	UNIXSOCKBUFFER_H_

# include <stdlib.h>
# include "ISockBuffer.hpp"

namespace ZlNetwork
{
  namespace Buffer
  {
    typedef size_t	SOCKBUFF_ULONG;

    struct ISockBuffer::SockBuffer
    {
      size_t len;
      char * buf;
    };

    class UnixSockBuffer :
      public ISockBuffer
    {
    public:

      UnixSockBuffer(void);
      virtual ~UnixSockBuffer(void);

      template<typename T>
      void SetBuffer(T * buffer, size_t length)
      {
	union {
	  char * vptr;
	  T * tptr;
	} tmp;
	tmp.tptr = buffer;
	_buff.buf = tmp.vptr;
	_buff.len = length;
      }

      virtual struct ISockBuffer::SockBuffer * GetLpBuffer(void);


    private:
      struct ISockBuffer::SockBuffer _buff;
    };

    template <typename T>
    void _SetBuffer(ISockBuffer * sockBuffer, T *buffer, SOCKBUFF_ULONG length)
    {
      UnixSockBuffer * usockbuffer = dynamic_cast<UnixSockBuffer *>(sockBuffer);
      if (usockbuffer)
	usockbuffer->SetBuffer<T>(buffer, length);
    }
  }
}

#endif		// !UNIXSOCKBUFFER_H_
