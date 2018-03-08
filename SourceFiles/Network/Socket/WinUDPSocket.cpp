#include "WinUDPSocket.hpp"
#include "WinSockBuffer.hpp"

ZlNetwork::Socket::WinUDPSocket::WinUDPSocket(void)
{
}

ZlNetwork::Socket::WinUDPSocket::~WinUDPSocket(void)
{
}

bool ZlNetwork::Socket::WinUDPSocket::Initialize(const std::string & address, const std::string & port)
{
	return AWinSocket::Initialize(AF_INET, SOCK_DGRAM, IPPROTO_UDP, address, port);
}

bool ZlNetwork::Socket::WinUDPSocket::Send(Buffer::ISockBuffer &buff, Resolver::IAddrInfo &addrinfo)
{
	DWORD NumberOfBytesSend = 0;
	if (addrinfo.GetResult() && buff.GetLpBuffer()->buf)
		return (WSASendTo(_socket, buff.GetLpBuffer(), 1, &NumberOfBytesSend, addrinfo.GetResult()->ai_flags, addrinfo.GetResult()->ai_addr, addrinfo.GetResult()->ai_addrlen, NULL, NULL) != SOCKET_ERROR &&
			NumberOfBytesSend == buff.GetLpBuffer()->len);
	return false;
}

bool ZlNetwork::Socket::WinUDPSocket::Receive(Buffer::ISockBuffer &buff, Resolver::IAddrInfo &addrinfo)
{
	DWORD NumberOfBytesRecvd = 0, Flags = 0;
	int csinlen = addrinfo.GetResult()->ai_addrlen;
	if (addrinfo.GetResult() && buff.GetLpBuffer()->buf &&
		WSARecvFrom(_socket, buff.GetLpBuffer(), 1, &NumberOfBytesRecvd, &Flags, addrinfo.GetResult()->ai_addr, &csinlen, NULL, NULL) != SOCKET_ERROR)
	{
		buff.GetLpBuffer()->len = NumberOfBytesRecvd;
		addrinfo.GetResult()->ai_addrlen = csinlen;
		addrinfo.GetResult()->ai_protocol = IPPROTO_UDP;
		addrinfo.GetResult()->ai_socktype = SOCK_DGRAM;
		addrinfo.GetResult()->ai_flags = Flags;
		return true;
	}
	return false;
}

ZlNetwork::Socket::IUDPSocket * ZlNetwork::Socket::CreateUDPSocket()
{
	return new WinUDPSocket();
}
