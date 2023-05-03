#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <iphlpapi.h>

#include "Server.h"
#include "SocketManager.h"
#include "MessagesManager.h"
#include "Callback.h"

#define DEFAULT_BUFLEN 512
#define WM_SOCKET WM_USER + 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;