#include "../include/server.h"
#include "../include/http_TCPServer.h"

using namespace http;

std::string ip = "0.0.0.0";
int port = 8080;


int server() {
TCPServer server(ip,port);


server.startListen();
    
    return 0;
}

