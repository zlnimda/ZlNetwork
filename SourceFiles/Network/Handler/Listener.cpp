#include	<algorithm>
#include	"Listener.hpp"

ZlNetwork::Handler::IValue::IValue() {}

ZlNetwork::Handler::IValue::~IValue() {}

ZlNetwork::Handler::Listener::Listener(IFunction * function, SocketService & arg1)
  : _function(function), _1(arg1)
{
}

ZlNetwork::Handler::Listener::~Listener()
{
  std::list<IValue *>::iterator it = _list.begin();

  for(; it != _list.end(); ++it)
    delete *it;
  delete _function;
}

ZlNetwork::Handler::Listener & ZlNetwork::Handler::Listener::operator()(IValue * arg)
{
  if (arg)
    _list.push_back(arg);
  return *this;
}

bool	ZlNetwork::Handler::Listener::Check(SocketService socket, Buffer::AdvSockBuffer & buffer)
{
  if (_function == NULL)
    return false;
  _1 = socket;
  std::list<IValue *>::iterator it = _list.begin();
  for (; it != _list.end(); it++)
    {
      if (!(**it)(buffer))
      	return false;
    }
  return (*_function)();
}

ZlNetwork::Handler::Sender::Sender() {}

ZlNetwork::Handler::Sender::~Sender() {}

ZlNetwork::Handler::Sender & ZlNetwork::Handler::Sender::operator()(IValue * arg)
{
  if (arg)
    _list.push_back(arg);
  return *this;
}

void	ZlNetwork::Handler::Sender::FillIt(Buffer::AdvSockBuffer & buffer)
{
  std::list<IValue *>::iterator it = _list.begin();
  for (; it != _list.end(); it++)
    (**it) >> buffer;
  buffer.setToWrite();
}
