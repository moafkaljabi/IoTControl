void TCPServer::handleClient(int clientSocket) {
    char buffer[2048] = {0};

    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0) {
            std::cerr << "Error receiving data from client socket: " << strerror(errno) << std::endl;
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Client disconnected: " << clientSocket << std::endl;
            break;
        }

        std::cout << "Message from client (" << clientSocket << "): " << buffer << std::endl;

        // Send JSON response
        sendJSON(clientSocket);
    }

    close(clientSocket);
}