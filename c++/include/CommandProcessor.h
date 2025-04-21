/*

2025

This class is to process commands after receiving them from the JSONReceiver class.



[TCPServer]
     ↓
[ClientHandler] ← receives string over socket
     ↓
[JSONReceiver] ← parses it into JSON object
     ↓
[CommandProcessor] ← interprets & runs actions based on command
     ↓
[JSONSender] ← sends result/status response back



*/


#pragma once 


class CommandProcessor {

public:

    CommandProcessor();
    ~CommandProcessor();
 

private:



};
