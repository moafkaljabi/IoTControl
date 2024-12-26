/*

1- Create the socket.

2- Define our address.

3- Bind

4- Listen

5- Accept

6- Recv

7- Close

- concurrency

gLock - 


- Error Handling  - Protocol design - Security  - Data Handling

*/

/*

create a vector for sockts ton/
create a vector to manage the threads.

accept() -> creates new thread with each new connection.

close()  -> removed the thread of the connection. 

int accept() {
   try std::thread
    if (accept()){
    create new thread for the accepted client.
    }

}

*/

#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

std::vector<int> clientSockets; // Store client sockets
std::vector<std::thread> clientThreads; // Store client threads

void handleClient(int clientSocket) {
    char buffer[2048] = {0};
    
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cout << "Client disconnected or error occurred. Closing socket: " << clientSocket << std::endl;
            close(clientSocket);
            return;
        }

        std::cout << "Message from client (" << clientSocket << "): " << buffer << std::endl;
        // Process the received message and send a response if needed
        send(clientSocket, "Message received", strlen("Message received"), 0);
    }
}

int main() {
    // Create the socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create server socket!" << std::endl;
        return 1;
    }

    // Define the address
    sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(8080);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) {
        std::cerr << "Failed to bind server socket!" << std::endl;
        return 1;
    }

    // Listen
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "Failed to listen on server socket!" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Accept connections
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept connection!" << std::endl;
            continue;
        }

        std::cout << "New client connected: " << clientSocket << std::endl;

        // Add client socket to vector
        clientSockets.push_back(clientSocket);

        // Create a thread to handle the client
        clientThreads.emplace_back(std::thread(handleClient, clientSocket));
    }

    // Close server socket (unreachable in this design)
    close(serverSocket);

    // Join threads (also unreachable here unless you add a shutdown condition)
    for (std::thread& t : clientThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}



/*


for error handling: 
Check the return value of recv(). If recv() returns 0, it indicates that the client has closed the connection.
Log whether the disconnection was intentional (e.g., recv() returning 0) or due to an error (e.g., recv() returning -1).


Scaling Beyond Threads

Threads are suitable for a moderate number of clients. For thousands of connections, use asynchronous models (e.g., epoll or select) or frameworks like asio.


*/