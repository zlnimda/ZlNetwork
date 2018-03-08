#include	<iostream>
#include	"ZlNetwork.hpp"
#include	"ZRP.hpp"
#include	"CommunicateProtocol.hpp"

class CommunicateServer : protected CommunicateProtocol
{
public:

  CommunicateServer(const std::string & port)
  {
    ZlNetwork::Handler::SocketService Service;
    Service = CreateServerTCPSocket(*this, &CommunicateServer::AddStream, port);
    LisBonjour(*this, &CommunicateServer::ReceiveBonjour);
    LisTxtMsg(*this, &CommunicateServer::ReceiveTxtMsg);
  }

  void AddStream(ZlNetwork::Handler::SocketService Stream)
  {
    AddListener(Stream, "Bonjour");
  }

  void ReceiveBonjour(ZlNetwork::Handler::SocketService s, std::string Pseudo)
  {
    std::map<ZlNetwork::Handler::SocketService, std::string>::iterator it = Streams.begin();

    for (; it != Streams.end(); ++it)
      SendTxtMsg(it->first, "System", Pseudo + " has come.");
    DisableListener(s, "Bonjour");
    AddListener(s, "TxtMsg");
    Streams[s] = Pseudo;
    SendIdentified(s);
  }

  void ReceiveTxtMsg(ZlNetwork::Handler::SocketService s, std::string Pseudo, std::string Msg)
  {
    std::map<ZlNetwork::Handler::SocketService, std::string>::iterator it = Streams.begin();

    for (; it != Streams.end(); ++it)
		SendTxtMsg(it->first, Streams[s], Msg);
  }

  int Run()
  {
    while (42)
      Update();
    return 0;
  }

private:

  std::map<ZlNetwork::Handler::SocketService, std::string> Streams;
};

#pragma comment(lib,"Ws2_32.lib")
int main(int argc, char *argv[])
{
  if (argc > 1)
    {
      CommunicateServer Com(argv[1]);

      return Com.Run();
    }
  return -1;
}
