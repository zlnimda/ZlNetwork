#include <sys/socket.h>
#include "UnixUDPSocket.hpp"
#include "UnixSockBuffer.hpp"

ZlNetwork::Socket::UnixUDPSocket::UnixUDPSocket(void)
{
}

ZlNetwork::Socket::UnixUDPSocket::~UnixUDPSocket(void)
{
}

bool ZlNetwork::Socket::UnixUDPSocket::Initialize(const std::string & address, const std::string & port)
{
	return AUnixSocket::Initialize(AF_INET, SOCK_DGRAM, IPPROTO_UDP, address, port);
}

bool ZlNetwork::Socket::UnixUDPSocket::Send(Buffer::ISockBuffer &buff, Resolver::IAddrInfo &addrinfo)
{
	if (addrinfo.GetResult() && buff.GetLpBuffer()->buf)
		return (sendto(_socket, buff.GetLpBuffer()->buf, buff.GetLpBuffer()->len, addrinfo.GetResult()->ai_flags, addrinfo.GetResult()->ai_addr, addrinfo.GetResult()->ai_addrlen) != -1);
	return false;
}

bool ZlNetwork::Socket::UnixUDPSocket::Receive(Buffer::ISockBuffer &buff, Resolver::IAddrInfo &addrinfo)
{
	int nrecv = 0;
	socklen_t csinlen = addrinfo.GetResult()->ai_addrlen;
	if (addrinfo.GetResult() && buff.GetLpBuffer()->buf &&
		(nrecv = recvfrom(_socket, buff.GetLpBuffer()->buf, buff.GetLpBuffer()->len, addrinfo.GetResult()->ai_flags, addrinfo.GetResult()->ai_addr, &csinlen)) != -1)
	{
		buff.GetLpBuffer()->len = nrecv;
		addrinfo.GetResult()->ai_addrlen = csinlen;
		addrinfo.GetResult()->ai_protocol = IPPROTO_UDP;
		addrinfo.GetResult()->ai_socktype = SOCK_DGRAM;
		return true;
	}
	return false;
}

ZlNetwork::Socket::IUDPSocket * ZlNetwork::Socket::CreateUDPSocket()
{
	return new UnixUDPSocket();
}
