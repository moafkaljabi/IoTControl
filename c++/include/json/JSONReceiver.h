/*

This class is responsible for receiving JSON and deserializing it into useful data.

*/

#pragma once 

#include <string>
#include <iostream>
#include <sys/socket.h> // For `send`

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>




class JSONReceiver
{

public:
    static void parseJSON(const std::string& jsonData);


private:

};
