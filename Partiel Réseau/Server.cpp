#include "Server.h"

Server::Server() {
	hSocket = INVALID_SOCKET;
}

int Server::ServerLaunch()
{

	int iResult;

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, "27015", &hints, &result);

	sManager.Startup(iResult);

	hSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (hSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return 1;
	}

	iResult = bind(hSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(hSocket);
		return 1;
	}

	freeaddrinfo(result);

	if (listen(hSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(hSocket);
		return 1;
	}

	return 0;
}

int Server::ServerConnect(SOCKET& ClientSocket, int cId)
{
	// Accept a client socket
	return sManager.Accept(ClientSocket, hSocket, cId);
}

int Server::ServerDisconnect(SOCKET& ClientSocket)
{
	int iResult = shutdown(ClientSocket, SD_SEND);
	return sManager.Shutdown(iResult, ClientSocket);
}

SOCKET Server::GetSocket()
{
	return hSocket;
}