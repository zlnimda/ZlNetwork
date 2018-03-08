#include	"AdvSockBuffer.hpp"

ZlNetwork::Buffer::AdvSockBuffer::AdvSockBuffer(SOCKBUFF_ULONG size)
{
  _buff = new char[size];
  _writer = _buff;
  _reader = _buff;
  _len = size;
  _isockBuff = CreateSockBuffer();
  SetBuffer(_isockBuff, _buff, _len);
}

ZlNetwork::Buffer::AdvSockBuffer::~AdvSockBuffer()
{
  delete _isockBuff;
  if (_buff)
    delete[] _buff;
}

template <>
ZlNetwork::Buffer::AdvSockBuffer & ZlNetwork::Buffer::AdvSockBuffer::operator<<<std::string>(std::string & val)
{
  short length = val.size();
  operator<<(length);
  for (short i = 0; i < length; ++i)
    operator<<(val[i]);
  return *this;
}

template <>
ZlNetwork::Buffer::AdvSockBuffer & ZlNetwork::Buffer::AdvSockBuffer::operator>><std::string>(std::string & val)
{
  short length;
  operator>>(length);
  val.clear();
  val.resize(length);
  for (short i = 0; i < length; ++i)
    operator>>(val[i]);
  return *this;
}


ZlNetwork::Buffer::ISockBuffer * ZlNetwork::Buffer::AdvSockBuffer::getSockBuffer() const
{
  return _isockBuff;
}

void ZlNetwork::Buffer::AdvSockBuffer::setLengthBuffer(SOCKBUFF_ULONG len)
{
  if (_isockBuff)
    _isockBuff->GetLpBuffer()->len = len;
}

void ZlNetwork::Buffer::AdvSockBuffer::reinit()
{
  if (_isockBuff)
    _isockBuff->GetLpBuffer()->len = _len;
  _reader = _buff;
  _writer = _buff;
}

void ZlNetwork::Buffer::AdvSockBuffer::setToWrite()
{
  setLengthBuffer(_writer - _buff);
}
