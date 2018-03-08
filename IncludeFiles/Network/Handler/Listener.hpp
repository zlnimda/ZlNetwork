#ifndef		ZL_LISTENER_HPP_
# define	ZL_LISTENER_HPP_

# include	"Function.hpp"
# include	"AdvSockBuffer.hpp"

namespace ZlNetwork
{
  namespace Handler
  {

    typedef unsigned int SocketService;

    class IValue
    {
    public:
      IValue();
      ~IValue();

      virtual bool operator()(Buffer::AdvSockBuffer & buffer) = 0;
      virtual void operator>>(Buffer::AdvSockBuffer & buffer) = 0;
      virtual IValue * copy() const = 0;
    };
	
	template <int I>
	class Arg : IArg
	{
		template <typename RET>
		RET GetValue(std::tuple & tuple)
		{
			return std::get<I>(tuple);
		}
	};


    template <typename T>
    class Catcher : public IValue
    {
    public:
      Catcher(T & storage) : _storage(storage) { }
      ~Catcher() { }

      virtual bool operator()(Buffer::AdvSockBuffer & buffer)
      {
	buffer >> _storage;
	return true;
      }

      virtual IValue * copy() const
      {
	return new Catcher<T>(_storage);
      }

      virtual void operator>>(Buffer::AdvSockBuffer & buffer)
      {
	buffer << _storage;
      }

    private:
      T & _storage;
    };


    template <typename T>
    class Checker : public IValue
    {
    public:
      Checker(T value) : _value(value) { }
      ~Checker() { }

      virtual bool operator()(Buffer::AdvSockBuffer & buffer)
      {
	T type;
	buffer >> type;
	return (type == _value);
      }

      virtual IValue * copy() const
      {
	return new Checker<T>(_value);
      }

      virtual void operator>>(Buffer::AdvSockBuffer & buffer)
      {
	buffer << _value;
      }

    private:
      T		_value;
    };


    class Listener
    {
    public:
      Listener(IFunction * function, SocketService & arg1);
      virtual ~Listener();

      virtual Listener & operator()(IValue * arg);

      bool Check(SocketService, Buffer::AdvSockBuffer & buffer);

    private:
      Listener(const Listener &);
      const Listener & operator=(const Listener &);

      IFunction * _function;
      SocketService & _1;
      std::list<IValue *> _list;
    };


    class Sender
    {
    public:
      Sender();
      virtual ~Sender();

      Sender & operator()(IValue *);

      void	FillIt(Buffer::AdvSockBuffer & buffer);

    private:
      Sender(const Sender&);
      const Listener & operator=(const Listener &);

      std::list<IValue *> _list;
    };
  }
}

#endif		//!ZL_LISTENER_HPP_
