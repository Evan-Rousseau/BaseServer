#include "utils.h"
#include "Server.h"

void createConsole() {
#define _CRT_SECURE_NO_WARNINGS

    FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
    AllocConsole();
    freopen_s(&fpstdout, "CONOUT$", "w", stdout);
    freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    freopen_s(&fpstdin, "CONIN$", "r", stdin);

}

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    createConsole();

    WSADATA wsaData;
    int iResult;
    Server* servSocket = new Server(hInstance);
    servSocket->init();

    while(1){}
}