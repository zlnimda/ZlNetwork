#include <sstream>
#include <sys/types.h>
#include <stdlib.h>
#include "UnixAddrInfo.hpp"

ZlNetwork::Resolver::UnixAddrInfo::UnixAddrInfo(const std::string & node, const std::string & port, int socktype, int protocol, int family)
  :_result(NULL), _wasCreated(false)
{
  struct addrinfo hints = { 0 };
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_protocol = protocol;
	int retval = getaddrinfo(node.c_str(), port.c_str(), &hints, &_result);
}

ZlNetwork::Resolver::UnixAddrInfo::UnixAddrInfo()
	:_result(new struct addrinfo), _wasCreated(true)
{
}

ZlNetwork::Resolver::UnixAddrInfo::~UnixAddrInfo(void)
{
	if (_wasCreated && _result)
		delete _result;
	else if (_result != NULL)
		freeaddrinfo(_result);
}

struct addrinfo * ZlNetwork::Resolver::UnixAddrInfo::GetResult(void) const
{
	return _result;
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Resolver::CreateAddrInfo(const std::string & node, const std::string & service, int socktype, int protocol, int family)
{
	return new UnixAddrInfo(node, service, socktype, protocol, family);
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Resolver::CreateAddrInfo()
{
  return CreateAddrInfo("0.0.0.0", "22");
}

std::string ZlNetwork::Resolver::UnixAddrInfo::GetIp() const
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

std::string ZlNetwork::Resolver::UnixAddrInfo::GetPort() const
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

bool ZlNetwork::Resolver::UnixAddrInfo::SameAs(IAddrInfo *other) const
{
  return (GetIp() == other->GetIp() && GetPort() == other->GetPort());
}
