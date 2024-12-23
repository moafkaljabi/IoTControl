#include "server.h"
#include <iostream>
#include <unistd.h>

namespace tcp 
{
    TCPServer::TCPServer(std::string ip_address, int port) 
        : m_ip_address(ip_address), m_port(port), 
          m_socket(0), m_new_socket(0), 
          m_socketAddress_len(sizeof(m_socketAddress))
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
    }

    TCPServer::~TCPServer()
    {
        closeServer();
    }

    int TCPServer::initializeSocket()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0) {
            return -1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
            return -1;
        }

        if (listen(m_socket, 1) < 0) {
            return -1;
        }

        return 0;
    }

    void TCPServer::start()
    {
        if (initializeSocket() < 0) {
            std::cerr << "Failed to start server" << std::endl;
            return;
        }

        std::cout << "Server listening on " << m_ip_address << ":" << m_port << std::endl;

        while (true) {
            acceptConnection();
            
            if (receiveData()) {
                // Process received data here
                sendData("Received");  // Simple acknowledgment
            }
            
            close(m_new_socket);
        }
    }

    void TCPServer::acceptConnection()
    {
        m_new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
    }

    bool TCPServer::receiveData()
    {
        char buffer[1024] = {0};
        int bytesReceived = read(m_new_socket, buffer, 1024);
        
        if (bytesReceived > 0) {
            std::cout << "Received: " << buffer << std::endl;
            return true;
        }
        return false;
    }

    bool TCPServer::sendData(const std::string& data)
    {
        return send(m_new_socket, data.c_str(), data.length(), 0) > 0;
    }

    void TCPServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
    }
}