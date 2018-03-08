#include "AWinSocket.hpp"
#include "WinAddrInfo.hpp"
#include "WinSockStartup.hpp"

ZlNetwork::Socket::AWinSocket::AWinSocket(void)
	:_socket(INVALID_SOCKET)
{
	WinSockStartup::Start();
}

ZlNetwork::Socket::AWinSocket::~AWinSocket(void)
{
	Close();
}

bool ZlNetwork::Socket::AWinSocket::Initialize(int family, int type, int protocol, const std::string & address, const std::string & port)
{
	if (_socket != INVALID_SOCKET)
		return false;
	if (!port.empty())
	{
		Resolver::WinAddrInfo addrinfo(address, port, type, protocol, family);
		ADDRINFOA * result = addrinfo.GetResult();
		if (result)
		{
			_socket = WSASocket(result->ai_family, result->ai_socktype, result->ai_protocol, NULL, 0, 0);
			if (!Bind(addrinfo))
				Close();
		}
	}
	else
		_socket = WSASocket(family, type, protocol, NULL, 0, 0);
	return (_socket != INVALID_SOCKET);
}

bool ZlNetwork::Socket::AWinSocket::Bind(Resolver::IAddrInfo & addrinfo)
{
	return (bind(_socket, addrinfo.GetResult()->ai_addr, addrinfo.GetResult()->ai_addrlen) == 0);
}

void ZlNetwork::Socket::AWinSocket::Close()
{
	if (_socket != INVALID_SOCKET)
		closesocket(_socket);
	_socket = INVALID_SOCKET;
}

bool ZlNetwork::Socket::AWinSocket::Poll(bool & read, bool & write)
{
	WSAPOLLFD	pollfd;
	pollfd.fd = _socket;
	pollfd.events = POLLRDNORM | POLLWRNORM;
	pollfd.revents = 0;
	int ret = WSAPoll(&pollfd, 1, 0);
	if (ret == SOCKET_ERROR || pollfd.revents & POLLERR || pollfd.revents & POLLHUP || pollfd.revents & POLLNVAL)
	{
		Close();
		return false;
	}
	if (!ret)
		return false;
	read = (pollfd.revents & POLLRDNORM) != 0;
	write = (pollfd.revents & POLLWRNORM) != 0;
	return true;
}

bool ZlNetwork::Socket::AWinSocket::IsValid() const
{
	return _socket != INVALID_SOCKET;
}
