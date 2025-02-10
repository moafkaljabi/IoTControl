#include "ClientHandler.h"
#include "json/JSONReceiver.h" // Include JSONReceiver
#include <cstring>
#include <sys/socket.h>

ClientHandler::ClientHandler(std::shared_ptr<boost::asio::ip::tcp::socket>socket)
:   clientSocket(socket),
    clientAddress (socket->remote_endpoint().address().to_string()),
    clientPort (socket->remote_endpoint().port()),
    jsonSender (socket, clientAddress, clientPort)
{}

void ClientHandler::handleClient()
{
    auto buffer = std::make_shared<boost::asio::streambuf>();

    boost::asio::async_read_until(*clientSocket, *buffer, '\n',
    [this, buffer](const boost::system::error_code& ec, size_t bytesTransferred)
    {
        if (!ec)
        {
            std::istream stream(buffer.get());
            std::string jsonData;
            std::getline(stream, jsonData); // Read full line of JSON
            
            std::cout << "Received from client: " << jsonData << std::endl;

            JSONReceiver::parseJSON(jsonData);

            jsonSender.sendJSON();
        }
        else
        {
            std::cerr << "Error reading data: " << ec.message() << std::endl;
        }
    });
}
