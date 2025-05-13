#pragma once

#include <string>
#include "rapidjson/document.h"

class JSONProcessor {
public:
    bool parse(const std::string& inputJson, rapidjson::Document& outputDocument);

    std::string buildHelloMessage();
    std::string buildResponse(const std::string& response);
    std::string buildError(const std::string& errorMessage);

private:
    std::string serialize(const rapidjson::Document& document);
};
