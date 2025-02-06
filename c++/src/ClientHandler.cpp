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
    auto buffer = std::make_shared<std::vector<char>>(2048);

    boost::asio::async_read(*clientSocket, boost::asio::buffer(*buffer),
    [this, buffer](const boost::system::error_code ec, size_t bytesTransferred)
    {
        if(!ec)
        {
            // Null terminate the received data
            buffer->resize(bytesTransferred);

            std::string jsonData(buffer->begin(), buffer->end());

            // Log received msg
            std::cout << "Received from client: " << jsonData<< std::endl;

            // Call JSON to parse
            JSONReceiver::parseJSON(jsonData);


            // Send JSON response back
            jsonSender.sendJSON();
        }
        else
        {
            std::cerr << "MSG: " << ec.message() << std::endl;
        }
    }
    );
}

