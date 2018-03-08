#include	<iostream>
#include <thread>
#include	"ZlNetwork.hpp"
#include	"ZRP.hpp"
#include	"CommunicateProtocol.hpp"

class CommunicateClient : protected CommunicateProtocol
{
public:
  CommunicateClient(const std::string & ip, const std::string & port, const std::string & Pseudo)
  {
    Stream = CreateClientTCPSocket(ip, port);
    LisIdentified(*this, &CommunicateClient::ReceiveIdentified);
    LisTxtMsg(*this, &CommunicateClient::ReceiveTxtMsg);
    AddListener(Stream, "Identified");
    SendBonjour(Stream, Pseudo);
  }

  void ReceiveIdentified(ZlNetwork::Handler::SocketService s)
  {
    std::cout << "Connected !" << std::endl;
    AddListener(Stream, "TxtMsg");
    DisableListener(Stream, "Identified");
  }

  void ReceiveTxtMsg(ZlNetwork::Handler::SocketService s, std::string Pseudo, std::string Msg)
  {
    std::cout << '[' << Pseudo << "] : " << Msg << std::endl;
  }

  void Spec()
  {
	  SocketHandler::Update();
  }

  int Run()
  {
   /* struct pollfd fds;
	
    fds.fd = 0;
    fds.events = POLLIN;*/
	std::thread th([this](CommunicateClient * c) {while (42) c->Spec(); }, this);
    while (42)
      {
			std::string msg;
			std::getline(std::cin, msg);
			if (msg.empty())
			  return 0;
			SendTxtMsg(Stream, "", msg);
      }
    return -1;
  }

private:

  ZlNetwork::Handler::SocketService Stream;
};

#pragma comment(lib, "Ws2_32.lib") 
int main(int argc, char *argv[])
{
  if (argc > 3)
    {
      CommunicateClient Com(argv[1], argv[2], argv[3]);

      return Com.Run();
    }
  return -1;
}
