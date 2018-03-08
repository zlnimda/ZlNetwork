#ifndef		SETBUFFER_HPP_
# define	SETBUFFER_HPP_

# ifdef _WIN32
#  include	"WinSockBuffer.hpp"
# else // LINUX
#  include	"UnixSockBuffer.hpp"
# endif

namespace ZlNetwork
{
  namespace Buffer
  {

    template <typename T>
    void	SetBuffer(ISockBuffer *sockBuffer, T *buffer, SOCKBUFF_ULONG length)
    {
      _SetBuffer(sockBuffer, buffer, length);
    }

  }
}

#endif		//!SETBUFFER_HPP_
