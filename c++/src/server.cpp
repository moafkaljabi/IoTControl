#include "../include/server.h" // Adjust path as per your project structure
#include "../include/http_TCPServer.h" // Include the necessary headers

void startServer() {
    using namespace http;

    TCPServer server("0.0.0.0", 8080); // Create a server instance
    server.startListen(); // Start listening for connections
}
