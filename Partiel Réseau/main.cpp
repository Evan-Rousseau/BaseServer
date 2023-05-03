#include "utils.h"

int main(int argc, char* argv[]) 
{
    //WNDCLASSEX wc;
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed : %d \n", iResult);
    }
    else {
        Server* servSocket = new Server();
        servSocket->ServerLaunch();
}