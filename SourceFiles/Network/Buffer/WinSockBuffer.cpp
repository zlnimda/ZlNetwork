#include "WinSockBuffer.hpp"

ZlNetwork::Buffer::WinSockBuffer::WinSockBuffer(void)
{
	_buff.buf = NULL;
	_buff.len = 0;
}

ZlNetwork::Buffer::WinSockBuffer::~WinSockBuffer(void)
{
}

struct ZlNetwork::Buffer::ISockBuffer::SockBuffer * ZlNetwork::Buffer::WinSockBuffer::GetLpBuffer(void)
{
	return &_buff;
}

ZlNetwork::Buffer::ISockBuffer * ZlNetwork::Buffer::CreateSockBuffer(void)
{
	return new WinSockBuffer();
}
