#include "SocketManager.h"

#define DEFAULT_PORT "27015"

SocketManager::SocketManager()
{
}

int SocketManager::Startup(int iResult) {
    // Initialize Winsock
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
    return 0;
}

int SocketManager::GetInfo(int iResult, addrinfo hints, addrinfo** result) {
    // Resolve the server address and port
    iResult = getaddrinfo("10.1.171.36", DEFAULT_PORT, &hints, result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    return 0;
}

int SocketManager::Connect(int iResult, SOCKET& connectSocket, addrinfo* result, addrinfo* ptr) {
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (connectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    return 0;
}

int SocketManager::Accept(SOCKET connectSocket, SOCKET hSocket, int cId)
{
    connectSocket = accept(hSocket, NULL, NULL);
    if (connectSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(hSocket);
        return 1;
    }
    char msg[2];
    msg[0] = cId + '0';
    msg[1] = '\0';
    send(connectSocket, msg, (int)strlen(msg) + 1, 0);
    return 0;
}

int SocketManager::Send(int iResult, SOCKET connectSocket, std::string testsend)
{
    // Send an initial buffer
    const char* testsent = testsend.c_str();
    iResult = send(connectSocket, testsent, (int)strlen(testsent) + 1, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    printf("Bytes Sent: %ld\n", iResult);
    printf("sent : %s\n", testsent);
    return 0;
}

void SocketManager::Receive(int iResult, SOCKET connectSocket, char recvbuf[], int recvbuflen) {

    // Receive until the peer closes the connection
    memset(recvbuf, 0, sizeof(recvbuf));

    do {
        iResult = recv(connectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

        printf("received : %s\n", recvbuf);
        printf("\n");

    } while (strlen(recvbuf) == 0);
}

int SocketManager::Shutdown(int iResult, SOCKET connectSocket) {
    // shutdown the connection since no more data will be sent
    iResult = shutdown(connectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

void SocketManager::Cleanup(SOCKET connectSocket) {
    // cleanup
    closesocket(connectSocket);
    WSACleanup();
}