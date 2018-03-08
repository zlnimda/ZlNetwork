#include <iostream>
#include "WinTCPSocket.hpp"
#include "WinAddrInfo.hpp"
#include "WinSockBuffer.hpp"

ZlNetwork::Socket::WinTCPSocket::WinTCPSocket(void)
	:_isConnected(false), _addrInfo(NULL)
{
}

ZlNetwork::Socket::WinTCPSocket::WinTCPSocket(SOCKET s, Resolver::IAddrInfo * addrinfo)
	:_isConnected(false), _addrInfo(addrinfo)
{
	_socket = s;
	if (_socket != INVALID_SOCKET)
		_isConnected = true;
}

ZlNetwork::Socket::WinTCPSocket::~WinTCPSocket(void)
{
	if (_addrInfo != NULL)
		delete _addrInfo;
}

bool ZlNetwork::Socket::WinTCPSocket::Initialize(const std::string & address, const std::string & port)
{
	bool ret = AWinSocket::Initialize(AF_INET, SOCK_STREAM, IPPROTO_TCP, address, port);
	return ret;
}

bool ZlNetwork::Socket::WinTCPSocket::Listen(int backlog)
{
	return (listen(_socket, backlog) == 0);
}

ZlNetwork::Socket::ITCPSocket * ZlNetwork::Socket::WinTCPSocket::accept()
{
	Resolver::IAddrInfo * addrinfo = Resolver::CreateAddrInfo();
	ADDRINFOA * csin = addrinfo->GetResult();
	int csinlen = sizeof(*csin);
	SOCKET s = WSAAccept(_socket, csin->ai_addr, &csinlen, NULL, NULL);
	addrinfo->GetResult()->ai_addrlen = csinlen;
	if (s == INVALID_SOCKET)
		return NULL;
	return new WinTCPSocket(s, addrinfo);
}

bool ZlNetwork::Socket::WinTCPSocket::Connect(const std::string & address, const std::string & port)
{
	if (_isConnected)
		return false;
	_addrInfo = Resolver::CreateAddrInfo(address, port);
	ADDRINFOA * result = _addrInfo->GetResult();
	if (result)
		_isConnected = (WSAConnect(_socket, result->ai_addr, result->ai_addrlen, NULL, NULL, NULL, NULL) == 0);
	return _isConnected;
}

bool ZlNetwork::Socket::WinTCPSocket::Send(Buffer::ISockBuffer & buff)
{
	if (_isConnected)
	{
		DWORD NumberOfBytesSend = 0, Flags = 0;
		int ret = WSASend(_socket, buff.GetLpBuffer(), 1, &NumberOfBytesSend, 0, NULL, NULL);
		if (ret == SOCKET_ERROR)
			Close();
		return (ret == 0 && NumberOfBytesSend == buff.GetLpBuffer()->len);
	}
	return false;
}

bool ZlNetwork::Socket::WinTCPSocket::Receive(Buffer::ISockBuffer & buff)
{
	if (_isConnected)
	{
		DWORD NumberOfBytesRecvd = 0, Flags = 0;
		int ret = WSARecv(_socket, buff.GetLpBuffer(), 1, &NumberOfBytesRecvd, &Flags, NULL, NULL);
		if (ret == SOCKET_ERROR || NumberOfBytesRecvd == 0)
			Close();
		else
			buff.GetLpBuffer()->len = NumberOfBytesRecvd;
		return (ret == 0);
	}
	return false;
}

bool ZlNetwork::Socket::WinTCPSocket::IsConnected() const
{
	return _isConnected;
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Socket::WinTCPSocket::GetConnectionInfo() const
{
	return _addrInfo;
}

void ZlNetwork::Socket::WinTCPSocket::Close()
{
	_isConnected = false;
	AWinSocket::Close();
}

ZlNetwork::Socket::ITCPSocket * ZlNetwork::Socket::CreateTCPSocket()
{
	return new WinTCPSocket();
}
