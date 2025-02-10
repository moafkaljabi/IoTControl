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

#include <TCPServer.h>


TCPServer::TCPServer(int port) : acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))
{
    
}

void TCPServer::start()
{
    std::cout << "Server is listening..." << std::endl;

    acceptConnection();

    size_t numThreads = std::thread::hardware_concurrency();

    for(size_t i=0; i<numThreads; ++i) 
    {
        threadPool.emplace_back([this]() {ioc.run();});
    }

    for( auto& thread : threadPool) 
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
}


void TCPServer::acceptConnection()
{
    auto socket = std::make_shared<boost::asio::ip::tcp::socket> (ioc);

    acceptor.async_accept(*socket, [this, socket](const boost::system::error_code& error)
    {
        if(!error)
        {
            std::cout << "New client connected: " << socket->remote_endpoint() << std::endl;

            // clientHandler.emplace(socket);
            // clientHandler->handleClient();

            auto clientHandler = std::make_shared<ClientHandler>(socket);
            clientHandler->handleClient();
        }

        // To accept the next client
        acceptConnection();
    });
}


void TCPServer::stop()
{
    ioc.stop();

    for(auto& thread : threadPool) 
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
}
