#pragma once
#include "utils.h"

class Server
{
private:
	SOCKET hSocket = INVALID_SOCKET;
	SocketManager sManager;
public:
	Server();

	int ServerLaunch();
	int ServerConnect(SOCKET& ClientSocket, int cId);
	int ServerDisconnect(SOCKET& ClientSocket);

	SOCKET GetSocket();
};