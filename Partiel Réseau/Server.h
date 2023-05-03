#pragma once
#include "utils.h"
#include "HTTPRequestHandler.h"
class Server
{
    HWND hwnd_;
    HINSTANCE& hInstance_;
    WNDCLASSEX wc_;

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket;
    std::vector<SOCKET> v_clientSockets;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    HTTPRequestHandler* requestHandler;

public:
    Server(_In_ HINSTANCE hInstance);
    ~Server();
    int GetNBClientConnect() { return v_clientSockets.size(); }

    bool LaunchServer();
    void CreateHiddenEventWindow();
    void CreateListenSocket();

    void openClientSocket(WPARAM wParam);
    void closeClientSocket(WPARAM wParam);
    int findSocket(int socketValue);

    int findBufferLen(int socketIndex);
    string recieveClientData(int socketIndex);
    bool sendClientData(int socketIndex, string msg);

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Server* me = (Server*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (me) return me->realWndProc(hwnd, msg, wParam, lParam);
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    LRESULT CALLBACK realWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    bool ProcessMessage();
    void closeServer();
};