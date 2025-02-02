#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

class TCPServer {
public:
    TCPServer(int port);
    ~TCPServer();
    void start();

private:
    int serverSocket;
    int port;
    sockaddr_in sockAddr;
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;

  
    void closeServer();
};

#endif // TCPSERVER_H
