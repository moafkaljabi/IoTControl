/*

2025

JSONProcessor.h

*/


#pragma once 

#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


class JSONProcessor {

public:
    // Parse JSON
    bool parse(const std::string& inputJson, const rapidjson::Document& outputDocument);

    // Build the messages
    std::string buildHelloMessage();
    std::string buildResponse(const std::string& response);
    std::string buildError(const std::string& errorMessage);

private:
    // Internal helper, serialzes json document to string
    std::string serialize(const rapidjson::Document& document);

};