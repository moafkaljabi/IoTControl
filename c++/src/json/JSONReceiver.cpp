/*

2025

- Responsible for parsing and validating incoming JSON.

- Could include schema validation in the future.

- Can be reused in MQTT flows too.  




*/



#include "JSONReceiver.h"



bool JSONReceiver::parseJSON(const std::string& jsonData, rapidjson::Document& docOut) 
{
    

    if (docOut.Parse(jsonData.c_str()).HasParseError())
    {
        std::cerr << "Failed to parse JSON from client: " << rapidjson::GetParseErrorFunc(docOut.GetParseError()) << std::endl;
        return false;
    }
    return true;
}
