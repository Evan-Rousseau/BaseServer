#include "HTTPRequestHandler.h"

HTTPRequestHandler::HTTPRequestHandler()
{
}

HTTPRequestHandler::~HTTPRequestHandler()
{
}

string HTTPRequestHandler::HandleRequest(string recivedHTTPRequest)
{
    string getRoute = GetHTTPRequest(recivedHTTPRequest);

    if (getRoute == "/") getRoute = DEFAULTROUTE;

    return GetHTTPResponse(getRoute);
}

string HTTPRequestHandler::GetHTTPRequest(string recivedHTTPRequest)
{
	string getRoute = "";

	size_t pos = recivedHTTPRequest.find("GET ");
	if (pos != -1)
	{
		size_t end_pos = recivedHTTPRequest.find(" HTTP/1", pos + 4);
		if (end_pos != -1)
		{
			getRoute = recivedHTTPRequest.substr(pos + 4, end_pos - (pos + 4));
		}
	}

	return getRoute;
}

string HTTPRequestHandler::GetFileContentType(string filename)
{
	if (filename.find(".html") != -1) return "text/html";
	else if (filename.find(".css") != -1) return "text/css";
	else return "text/plain";
}

string HTTPRequestHandler::GetHTTPResponse(string getRoute)
{
	string content = GetFileContent(getRoute);
	string contentType = GetFileContentType(getRoute);

	string httpResponse =
		"HTTP/1.1 200 OK \r\n"
		"Content-Type: " + contentType + "\r\n"
		"Content-Length: " + to_string(content.length()) + "\r\n"
		"\r\n"
		+ content;
    return httpResponse;
}

string HTTPRequestHandler::GetFileContent(string filename)
{
	string path = FILESPATH + filename;
	ifstream file(path);

	// Check if file is found and open
	if (!file.is_open()) {
		std::cout << "\n\n\nImpossible d'ouvrir le fichier\n\n\n" << std::endl;
		return "";
	}

	string content;
	string line;

	while (getline(file, line)) {
		content += line;
	}

	file.close();
	return content;
}
