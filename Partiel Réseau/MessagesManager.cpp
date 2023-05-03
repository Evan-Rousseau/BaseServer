#include "MessagesManager.h"

int MessagesManager::RecieveMessage(SOCKET& ClientSocket, char recvbuf[], char* rBuffer, int recvbuflen) {

    memset(recvbuf, 0, sizeof(recvbuf));
    do {
        int iResult = recv(ClientSocket, rBuffer, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
            printf("\n");
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            return 1;
        }

    } while (strlen(rBuffer) == 0);
    return 0;
}

vector<char*> MessagesManager::ParseMessage(char* rBuffer) {
    vector<char*> messages;
    const char* separator = "/";
    char* next_token = NULL;
    char* strToken = strtok_s(rBuffer, separator, &next_token);
    while (strToken != NULL) {
        printf("%s\n", strToken);
        messages.push_back(strToken);
        // On demande le token suivant.
        strToken = strtok_s(NULL, separator, &next_token);
    }
    return messages;
}