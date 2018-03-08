#include	<sys/socket.h>
#include	"UnixTCPSocket.hpp"
#include	"UnixAddrInfo.hpp"
#include	"UnixSockBuffer.hpp"

ZlNetwork::Socket::UnixTCPSocket::UnixTCPSocket(void)
  :_isConnected(false), _addrInfo(NULL)
{
}

ZlNetwork::Socket::UnixTCPSocket::UnixTCPSocket(int s, Resolver::IAddrInfo * addrinfo)
  :_isConnected(false), _addrInfo(addrinfo)
{
  _socket = s;
  if (_socket != -1)
    _isConnected = true;
}

ZlNetwork::Socket::UnixTCPSocket::~UnixTCPSocket(void)
{
  if (_addrInfo != NULL)
    delete _addrInfo;
}

bool ZlNetwork::Socket::UnixTCPSocket::Initialize(const std::string & address, const std::string & port)
{
  bool ret = AUnixSocket::Initialize(AF_INET, SOCK_STREAM, IPPROTO_TCP, address, port);
  return ret;
}

bool ZlNetwork::Socket::UnixTCPSocket::Listen(int backlog)
{
  return (listen(_socket, backlog) == 0);
}

ZlNetwork::Socket::ITCPSocket * ZlNetwork::Socket::UnixTCPSocket::accept()
{
  Resolver::IAddrInfo * addrinfo = Resolver::CreateAddrInfo();
  struct addrinfo * csin = addrinfo->GetResult();
  socklen_t csinlen = sizeof(*csin);
  int s = ::accept(_socket, csin->ai_addr, &csinlen);
  if (s == -1)
    return NULL;
  return new UnixTCPSocket(s, addrinfo);
}

bool ZlNetwork::Socket::UnixTCPSocket::Connect(const std::string & address, const std::string & port)
{
  if (_isConnected)
    return false;
  _addrInfo = Resolver::CreateAddrInfo(address, port);
  struct addrinfo * result = _addrInfo->GetResult();
  if (result)
    _isConnected = (connect(_socket, result->ai_addr, result->ai_addrlen) == 0);
  return _isConnected;
}

bool ZlNetwork::Socket::UnixTCPSocket::Send(Buffer::ISockBuffer & buff)
{
  if (_isConnected)
    {
      int Flags = 0;
      int ret = send(_socket, buff.GetLpBuffer()->buf, buff.GetLpBuffer()->len, Flags);
      if (ret <= -1)
	Close();
      return (ret > -1 && ret == buff.GetLpBuffer()->len);
    }
  return false;
}

bool ZlNetwork::Socket::UnixTCPSocket::Receive(Buffer::ISockBuffer & buff)
{
  if (_isConnected)
    {
      int Flags = 0;
      int ret = recv(_socket, buff.GetLpBuffer()->buf, buff.GetLpBuffer()->len, Flags);
      if (ret <= 0)
	Close();
      else
	buff.GetLpBuffer()->len = ret;
      return (ret > 0);
    }
  return false;
}

bool ZlNetwork::Socket::UnixTCPSocket::IsConnected() const
{
  return _isConnected;
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Socket::UnixTCPSocket::GetConnectionInfo() const
{
  return _addrInfo;
}

void ZlNetwork::Socket::UnixTCPSocket::Close()
{
  _isConnected = false;
  AUnixSocket::Close();
}

ZlNetwork::Socket::ITCPSocket * ZlNetwork::Socket::CreateTCPSocket()
{
  return new UnixTCPSocket();
}
