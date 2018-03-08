#include <iostream>
#include <sstream>
#include "WinAddrInfo.hpp"
#include "WinSockStartup.hpp"

ZlNetwork::Resolver::WinAddrInfo::WinAddrInfo(const std::string & node, const std::string & port, int socktype, int protocol, int family)
	:_result(NULL), _wasCreated(false)
{
	Socket::WinSockStartup::Start();
	ADDRINFOA hints = { 0 };
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_protocol = protocol;
	if (getaddrinfo(node.c_str(), port.c_str(), &hints, &_result) != 0)
		std::cerr << "Error when retrieve addrinfo" << std::endl;
}

ZlNetwork::Resolver::WinAddrInfo::WinAddrInfo()
	:_result(new struct addrinfo), _wasCreated(true)
{
	memset(_result, 0, sizeof(*_result));
	_result->ai_addr = new struct sockaddr;
	_result->ai_addrlen = sizeof(*_result->ai_addr);
	memset(_result->ai_addr, 0, _result->ai_addrlen);
}

ZlNetwork::Resolver::WinAddrInfo::~WinAddrInfo(void)
{
	if (_wasCreated && _result != NULL)
	{
		if (_result->ai_addr != NULL)
			delete _result->ai_addr;
		delete _result;
	}
	else if (_result != NULL)
		freeaddrinfo(_result);
}

struct addrinfo * ZlNetwork::Resolver::WinAddrInfo::GetResult(void) const
{
	return _result;
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Resolver::CreateAddrInfo(const std::string & node, const std::string & service, int socktype, int protocol, int family)
{
	return new WinAddrInfo(node, service, socktype, protocol, family);
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Resolver::CreateAddrInfo()
{
	return new WinAddrInfo();
}

std::string ZlNetwork::Resolver::WinAddrInfo::GetIp() const
{
  if (!_result)
    return "";
  union {
			struct sockaddr *csock;
			struct sockaddr_in * csin;
	} un;
  un.csock = _result->ai_addr;
	return inet_ntoa(un.csin->sin_addr);
}

std::string ZlNetwork::Resolver::WinAddrInfo::GetPort() const
{
  std::ostringstream oss;
  if (!_result)
    return "";
  union {
			struct sockaddr *csock;
			struct sockaddr_in * csin;
	} un;
  un.csock = _result->ai_addr;
  oss << ntohs(un.csin->sin_port);
	return oss.str();
}

bool ZlNetwork::Resolver::WinAddrInfo::SameAs(IAddrInfo *other) const
{
  return (GetIp() == other->GetIp() && GetPort() == other->GetPort());
}
