#include <iostream>
#include <server.h>

std::string ip = "0.0.0.0";
int port = 8080;

using namespace tcp;

int main(){

    TCPServer server(ip,port);

    server.start();

    return 0;
}