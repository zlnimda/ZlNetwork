#ifndef		ZL_ADVSOCKBUFFER_H_
# define	ZL_ADVSOCKBUFFER_H_

# include <memory>
# include <string>
# include <list>
# include "SetBuffer.hpp"

namespace ZlNetwork
{
  namespace Buffer
  {
    class	AdvSockBuffer
    {
    public:

      AdvSockBuffer(SOCKBUFF_ULONG size);
      virtual ~AdvSockBuffer(void);

      template <typename T>
      AdvSockBuffer & operator<<(T & val)
      {
	union {
	  T * in;
	  char * out;
	} un = { &val };
	while (un.in < &val + 1 &&
	       _writer < _buff + _len)
	  *(_writer++) = *(un.out++);
	return *this;
      }

    template <typename T>
    AdvSockBuffer & operator<<(std::list<T> & val)
    {
      typename std::list<T>::iterator it = val.begin();
      short length = val.size();
      operator<<(length);
      for (; it != val.end(); it++)
	operator<<(*it);
      return *this;
    }


      template <typename T>
      AdvSockBuffer & operator>>(T & val)
      {
	union {
	  T * in;
	  char * out;
	} un = { &val };
	while (un.in < &val + 1 &&
	       _reader < _buff + _len)
	  *(un.out++) = *(_reader++);
	return *this;
      }

      template <typename T>
      AdvSockBuffer & operator>>(std::list<T> & val)
      {
	val.clear();
	short length;
	operator>>(length);
	while (length-- > 0)
	  {
	    T new_val;
	    operator>>(new_val);
	    val.push_back(new_val);
	  }
	return *this;
      }

      ISockBuffer *	getSockBuffer() const;
      void		setLengthBuffer(SOCKBUFF_ULONG);
      void		reinit();
      void		setToWrite();

    private:
      AdvSockBuffer(const AdvSockBuffer &);
      const AdvSockBuffer & operator=(const AdvSockBuffer &);

      char *		_writer;
      char *		_reader;
      char *		_buff;
      SOCKBUFF_ULONG	_len;
      ISockBuffer	*_isockBuff;
    };

    template<> AdvSockBuffer & AdvSockBuffer::operator<<<std::string>(std::string & val);
    template<> AdvSockBuffer & AdvSockBuffer::operator>><std::string>(std::string & val);

  }
}

#endif		//!ADVSOCKBUFFER_H_
