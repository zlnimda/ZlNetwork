#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include "AUnixSocket.hpp"
#include "UnixAddrInfo.hpp"

ZlNetwork::Socket::AUnixSocket::AUnixSocket(void)
  :_socket(-1)
{
}


ZlNetwork::Socket::AUnixSocket::~AUnixSocket(void)
{
  Close();
}

bool ZlNetwork::Socket::AUnixSocket::Initialize(int family, int type, int protocol, const std::string & address, const std::string & port)
{
  if (_socket != -1)
    return false;
  if (!port.empty() || !address.empty())
    {
      Resolver::UnixAddrInfo addrinfo(address, port, type, protocol, family);
      struct addrinfo * result = addrinfo.GetResult();
      if (result)
	{
	  _socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	  if (!Bind(addrinfo))
	    Close();
	}
    }
  else
    _socket = socket(family, type, protocol);
  return (_socket != -1);
}

bool ZlNetwork::Socket::AUnixSocket::Bind(Resolver::IAddrInfo & addrinfo)
{
  return (bind(_socket, addrinfo.GetResult()->ai_addr, addrinfo.GetResult()->ai_addrlen) == 0);
}

void ZlNetwork::Socket::AUnixSocket::Close()
{
  if (_socket != -1)
    close(_socket);
  _socket = -1;
}

bool ZlNetwork::Socket::AUnixSocket::Poll(bool & read, bool & write)
{
  struct pollfd	pollfd;
  pollfd.fd = _socket;
  pollfd.events = POLLRDNORM | POLLWRNORM;
  pollfd.revents = 0;
  int ret = poll(&pollfd, 1, 0);
  if (ret == -1 || pollfd.revents & POLLERR || pollfd.revents & POLLHUP || pollfd.revents & POLLNVAL)
    {
      Close();
      return false;
    }
  if (!ret)
    return false;
  read = pollfd.revents & POLLRDNORM;
  write = pollfd.revents & POLLWRNORM;
  return true;
}

bool ZlNetwork::Socket::AUnixSocket::IsValid() const
{
  return _socket != -1;
}
