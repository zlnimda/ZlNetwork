#include "UnixSockBuffer.hpp"

ZlNetwork::Buffer::UnixSockBuffer::UnixSockBuffer(void)
{
	_buff.buf = NULL;
	_buff.len = 0;
}

ZlNetwork::Buffer::UnixSockBuffer::~UnixSockBuffer(void)
{
}

struct ZlNetwork::Buffer::ISockBuffer::SockBuffer * ZlNetwork::Buffer::UnixSockBuffer::GetLpBuffer(void)
{
	return &_buff;
}

ZlNetwork::Buffer::ISockBuffer * ZlNetwork::Buffer::CreateSockBuffer(void)
{
	return new UnixSockBuffer();
}
