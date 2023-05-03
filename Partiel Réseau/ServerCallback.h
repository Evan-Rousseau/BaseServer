#pragma once
#include "utils.h"

class ServerCallback
{
public:
	virtual void callBack(string msg, int socketIndex) = 0;
};

