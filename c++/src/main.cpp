#include "TCPServer.h"

int main()
{
    try 
    {
        TCPServer server(8080);
        server.start();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Server error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
