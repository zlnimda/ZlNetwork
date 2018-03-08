#include	<iostream>
#include	"WinSockStartup.hpp"

ZlNetwork::Socket::WinSockStartup::WinSockStartup(void)
{
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
		std::cerr << "Failed to load WSADLL" << std::endl;
}

ZlNetwork::Socket::WinSockStartup::~WinSockStartup(void)
{
	WSACleanup();
	//if (WSACleanup() != 0)
	//	std::cout << "Failed to cleanup correctly WSADLL" << std::endl;
}

void ZlNetwork::Socket::WinSockStartup::Start(void)
{
	static WinSockStartup _instance;
}
