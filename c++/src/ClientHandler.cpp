#include "ClientHandler.h"
#include "json/JSONReceiver.h"
#include <cstring>
#include <sys/socket.h>

ClientHandler::ClientHandler(std::shared_ptr<boost::asio::ip::tcp::socket>socket)
:   clientSocket(socket),
    clientAddress (socket->remote_endpoint().address().to_string()),
    clientPort (socket->remote_endpoint().port()),
    buffer(std::make_shared<std::vector<char>>(1024)),
    jsonSender (std::make_shared<JSONSender>(socket, clientAddress, clientPort))
{}


void ClientHandler::handleClient()
{
    auto buffer = std::make_shared<boost::asio::streambuf>();

    boost::asio::async_read_until(*clientSocket, *buffer, '\n',
    [this, self = shared_from_this(), buffer](const boost::system::error_code& ec, size_t bytesTransferred)
    {
        if (!ec)
        {
            std::istream stream(buffer.get());
            std::string jsonData;
            std::getline(stream, jsonData); // Read full line of JSON
            
            std::cout << "Received from client: " << jsonData << std::endl;

            JSONReceiver::parseJSON(jsonData);

            if (jsonSender)
            {
                jsonSender->sendJSON(); // Ensure jsonSender is valid
            }
            else
            {
                std::cerr << "Error: jsonSender is null!" << std::endl;
            }

  
            if (clientSocket->is_open())
            {
                handleClient();
            }
            else
            {
                std::cerr << "Client socket closed, stopping read loop." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error reading data: " << ec.message() << std::endl;
            clientSocket->close();
        }
    });
}
