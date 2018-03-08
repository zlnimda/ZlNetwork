#include	"SocketHandler.hpp"

ZlNetwork::Handler::SocketHandler::SocketHandler()
  :_buff(5000)
{
}

ZlNetwork::Handler::SocketHandler::~SocketHandler()
{
  for(std::map<SocketService, Service *>::iterator it = _map.begin();
      it != _map.end(); it++)
    delete it->second;
  for(std::map<std::string, Listener *>::iterator it = _listener.begin();
      it != _listener.end(); it++)
    delete it->second;
}

ZlNetwork::Handler::SocketHandler::Service::Service()
{
  tcp = false;
  server = false;
  stcp = NULL;
  accept = NULL;
  _1_accept = NULL;
  addr = Resolver::CreateAddrInfo();
}

ZlNetwork::Handler::SocketHandler::Service::~Service()
{
  if (tcp)
    delete stcp;
  else
    delete sudp;
  if (accept != NULL)
    delete accept;
  for(std::list<Sender *>::iterator it = _sender.begin();
      it != _sender.end(); it++)
    delete *it;
  if (addr)
    delete addr;
  for(std::list<Resolver::IAddrInfo *>::iterator it = listUdp.begin();
    it != listUdp.end(); it++)
    if (*it)
      delete *it;
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::AddTCPService(Socket::ITCPSocket *tcp)
{
  Service * service = new Service;
  if (service &&
      (service->stcp = tcp))
    {
      SocketService id = counter++;
      service->tcp = true;
      _map[id] = service;
      return id;
    }
  delete service;
  return FailSocket;
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::AddUDPService(Socket::IUDPSocket *udp)
{
  Service * service = new Service;
  if (service &&
      (service->sudp = udp))
    {
      SocketService id = counter++;
      _map[id] = service;
      return id;
    }
  delete service;
  return FailSocket;
}


ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::CreateTCPSocket()
{
  return AddTCPService(ZlNetwork::Socket::CreateTCPSocket());
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::CreateUDPSocket(const std::string & port, const std::string & addr)
{
  ZlNetwork::Socket::IUDPSocket * udp = ZlNetwork::Socket::CreateUDPSocket();
  if (udp && udp->Initialize(addr, port))
	{
    return AddUDPService(udp);
	}
  delete udp;
  return FailSocket;
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::CreateUDPSocket()
{
  ZlNetwork::Socket::IUDPSocket * udp = ZlNetwork::Socket::CreateUDPSocket();
  if (udp && udp->Initialize())
    return AddUDPService(udp);
  delete udp;
  return FailSocket;
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::counter = 1;

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::FailSocket = 0;

void	ZlNetwork::Handler::SocketHandler::AddSender(SocketService s, Sender *sender)
{
  if (sender && _map.find(s) != _map.end())
    _map[s]->_sender.push_back(sender);
}

void	ZlNetwork::Handler::SocketHandler::addListener(const std::string &name, Listener *listener)
{
  if (listener)
    {
      if (_listener.find(name) != _listener.end())
	delete _listener[name];
      _listener[name] = listener;
    }
}

void	ZlNetwork::Handler::SocketHandler::UpdateTCPRead(SocketService id)
{
  _buff.reinit();
  _map[id]->stcp->Receive(*_buff.getSockBuffer());
  std::map<std::string, bool>::iterator it = _map[id]->rules.begin();
  for(; it != _map[id]->rules.end(); it++)
    {
      _buff.reinit();
      if (it->second &&
	  _listener[it->first]->Check(id, _buff))
	return ;
    }
}

void	ZlNetwork::Handler::SocketHandler::UpdateTCPWrite(SocketService id)
{
  Sender * sender = _map[id]->_sender.front();
  _buff.reinit();
  sender->FillIt(_buff);
  _map[id]->stcp->Send(*_buff.getSockBuffer());
  delete sender;
  _map[id]->_sender.pop_front();
}

bool	ZlNetwork::Handler::SocketHandler::UpdateTCP(SocketService id)
{
  bool read, write;
  Service * service = _map[id];
  if (!service->stcp->IsValid())
    {
      delete service;
      _map.erase(id);
      return false;
    }
  if (!service->stcp->Poll(read, write))
    return true;
  if (service->server)
    {
      if (!read)
	return true;
      SocketService idAccept = AddTCPService(service->stcp->accept());
      _map[idAccept]->rules = _map[id]->rules;
      *(service->_1_accept) = idAccept;
      (*service->accept)();
    }
  if (read && service->stcp->IsValid())
    UpdateTCPRead(id);
  if (!_map[id]->_sender.empty() && write && service->stcp->IsValid())
    UpdateTCPWrite(id);
  return true;
}

void	ZlNetwork::Handler::SocketHandler::UpdateUDPRead(SocketService id)
{
  _buff.reinit();
  _map[id]->sudp->Receive(*_buff.getSockBuffer(), *_map[id]->addr);
  std::map<std::string, bool>::iterator it = _map[id]->rules.begin();
  for(; it != _map[id]->rules.end(); it++)
    {
      _buff.reinit();
      if (it->second &&
	  _listener[it->first]->Check(id, _buff))
	return ;
    }
}

void	ZlNetwork::Handler::SocketHandler::UpdateUDPWrite(SocketService id)
{
  Sender * sender = _map[id]->_sender.front();
  _buff.reinit();
  sender->FillIt(_buff);
  for (std::list<Resolver::IAddrInfo *>::iterator it = _map[id]->listUdp.begin();
    it != _map[id]->listUdp.end(); it++)
    _map[id]->sudp->Send(*_buff.getSockBuffer(), **it);
  delete sender;
  _map[id]->_sender.pop_front();
}

bool	ZlNetwork::Handler::SocketHandler::UpdateUDP(SocketService id)
{
	bool read, write;
  Service * service = _map[id];
  if (!service->sudp->IsValid())
    {
      delete service;
      _map.erase(id);
      return false;
    }
	if (!service->sudp->Poll(read, write))
  if (!service->sudp->Poll(read, write))
    return true;
  if (read && service->sudp->IsValid())
    UpdateUDPRead(id);
  if (!_map[id]->_sender.empty() && !_map[id]->listUdp.empty() && write && service->sudp->IsValid())
    UpdateUDPWrite(id);
  return true;
}

void	ZlNetwork::Handler::SocketHandler::Update()
{
  std::map<SocketService, Service *>::iterator it = _map.begin();
  for(; it != _map.end() ; ++it)
  {
    if (it->second && it->second->tcp &&
      !UpdateTCP(it->first))
    {
      it = _map.begin();
      if (it == _map.end())
        return;
    }
    if (it->second && !it->second->tcp &&
      !UpdateUDP(it->first))
    {
      it = _map.begin();
      if (it == _map.end())
        return;
    }
  }
}

ZlNetwork::Handler::SocketService ZlNetwork::Handler::SocketHandler::CreateClientTCPSocket(const std::string & addr, const std::string & port)
{
  SocketService client = CreateTCPSocket();
  _map[client]->stcp->Initialize();
  if (_map[client]->stcp->Connect(addr, port))
    return client;
  delete _map[client];
  _map.erase(client);
  return FailSocket;
}

void  ZlNetwork::Handler::SocketHandler::AddListener(SocketService s, const std::string & name)
{
  if (_map.find(s) != _map.end() && _listener.find(name) != _listener.end())
    _map[s]->rules[name] = true;
}

void  ZlNetwork::Handler::SocketHandler::DisableListener(SocketService s, const std::string & name)
{
  SetEnablenessListener(s, name, false);
}

void  ZlNetwork::Handler::SocketHandler::EnableListener(SocketService s, const std::string & name)
{
  SetEnablenessListener(s, name, true);
}

void  ZlNetwork::Handler::SocketHandler::SetEnablenessListener(SocketService s, const std::string & name, bool value)
{
  if (_map.find(s) != _map.end() &&
      _map[s]->rules.find(name) != _map[s]->rules.end())
    _map[s]->rules[name] = value;
}

std::string ZlNetwork::Handler::SocketHandler::GetIp(SocketService s)
{
   if (_map.find(s) == _map.end())
      return "";
   else if (_map[s]->tcp && _map[s]->stcp->GetConnectionInfo())
     return _map[s]->stcp->GetConnectionInfo()->GetIp();
   else
     return "";
}

bool	ZlNetwork::Handler::SocketHandler::IsValid(SocketService s)
{
  return (_map.find(s) != _map.end());
}

ZlNetwork::Resolver::IAddrInfo * ZlNetwork::Handler::SocketHandler::getLastFromUdp(SocketService s)
{
  if (_map.find(s) != _map.end() && !_map[s]->tcp)
    return (_map[s]->addr);
  return NULL;
}

void  ZlNetwork::Handler::SocketHandler::addResolverId(SocketService s, Resolver::IAddrInfo *addr)
{
  if (_map.find(s) != _map.end() && !_map[s]->tcp)
  {
    std::list<Resolver::IAddrInfo *>::iterator it = _map[s]->listUdp.begin();
    for(; it != _map[s]->listUdp.end(); it++)
      if (addr->SameAs(*it))
        return ;
    _map[s]->listUdp.push_back(addr);
  }
}

void  ZlNetwork::Handler::SocketHandler::removeResolverId(SocketService s, Resolver::IAddrInfo *addr)
{
  if (_map.find(s) != _map.end() && !_map[s]->tcp)
  {
    std::list<Resolver::IAddrInfo *>::iterator it = _map[s]->listUdp.begin();
    for(; it != _map[s]->listUdp.end(); it++)
      if (addr->SameAs(*it))
      {
        _map[s]->listUdp.erase(it);
        return ;
      }
  }
}
