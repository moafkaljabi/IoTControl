#ifndef INCLUDED_TCP_SERVER
#define INCLUDED_TCP_SERVER

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

namespace tcp
{
    class TCPServer 
    {
    public:
        TCPServer(std::string ip_address, int port);
        ~TCPServer();
        void start();
        
    private:
        std::string m_ip_address;
        int m_port;
        int m_socket;
        int m_new_socket;
        struct sockaddr_in m_socketAddress;
        unsigned int m_socketAddress_len;
        
        int initializeSocket();
        void closeServer();
        void acceptConnection();
        bool receiveData();
        bool sendData(const std::string& data);
    };
} 

#endif