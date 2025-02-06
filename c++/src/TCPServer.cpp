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

            // Buffer to read the incoming data
            auto buffer = std::make_shared<std::vector<char>>(1024); 

            // Handle the client asynchronously
            boost::asio::async_read(
                *socket, boost::asio::buffer(*buffer),
                [this, socket, buffer](const boost::system::error_code& ec, size_t bytesTransferred)
                {
                    if(!ec) 
                    {
                        std::cout << "Received: " << bytesTransferred << " bytes" << std::endl;
                        // Optionally process the data here or offload to another thread
                    }
                    else {
                        std::cerr << "Error: " << ec.message() << std::endl;
                    }
                }
            );
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
