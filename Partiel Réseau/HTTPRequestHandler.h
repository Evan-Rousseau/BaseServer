#pragma once
#include "utils.h"
class HTTPRequestHandler
{
public:
	HTTPRequestHandler();
	~HTTPRequestHandler();

	string HandleRequest(string recivedHTTPRequest);

	string GetHTTPRequest(string recivedHTTPRequest);
	string GetFileContentType(string filename);

	string GetHTTPResponse(string getRoute);

	string GetFileContent(string filename);
};

