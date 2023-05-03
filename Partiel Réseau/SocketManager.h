#pragma once
#include "utils.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class SocketManager
{
private:

public:
	SocketManager();
	int Startup(int result);
	int GetInfo(int iResult, addrinfo hints, addrinfo** result);
	int Connect(int iResult, SOCKET& connectSocket, addrinfo* result, addrinfo* ptr);
	int Accept(SOCKET connectSocket, SOCKET hSocket, int cId);
	int Send(int iResult, SOCKET connectSocket, std::string testsend);
	void Receive(int iResult, SOCKET connectSocket, char recvbuf[], int recvbuflen);
	int Shutdown(int iResult, SOCKET connectSocket);
	void Cleanup(SOCKET connectSocket);
};