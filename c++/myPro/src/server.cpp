/*

1- Create the socket.

2- Define our address.

3- Bind

4- Listen

5- Accept

6- Recv

7- Close

*/

#include <sys/socket.h> // to use socket()
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

int main()
{

    // Create the socket, using socket()
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the address
    sockaddr_in sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(8080);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(
        serverSocket,
        (struct sockaddr*)&sockAddr,
        sizeof(sockAddr));

        // Listen 
        listen(serverSocket,10);

        // Accept
        int clientSocket = accept(serverSocket,nullptr,nullptr);

        // Create buffer
        char buffer [2048]= {0};

        // Recieve
        recv(clientSocket, buffer, sizeof(buffer),0);

        std::cout << "Message from the client: " << buffer << std::endl;

        // Close the connection
        close(serverSocket);

    return 0;
}