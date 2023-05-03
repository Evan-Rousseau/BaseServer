#pragma once
#include "utils.h"

class MessagesManager
{
private:

public:
	int RecieveMessage(SOCKET& ClientSocket, char recvbuf[], char* rBuffer, int recvbuflen);
	vector<char*> ParseMessage(char* rBuffer);
};