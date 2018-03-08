#ifndef		ISOCKETBUFFER_H_
# define	ISOCKETBUFFER_H_

namespace ZlNetwork
{
  namespace Buffer
  {
    class ISockBuffer
    {
    public:
      struct SockBuffer;

      ISockBuffer(void) { }
      virtual ~ISockBuffer(void) { }

      virtual struct SockBuffer * GetLpBuffer(void) = 0;
    };

    ISockBuffer * CreateSockBuffer(void);

  }
}

#endif		// ISOCKETBUFFER_H_
