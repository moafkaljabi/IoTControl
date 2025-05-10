/*

2025

JSONProcessor.cpp

*/


#include "JSONProcessor.h"

bool JSONProcessor::parse(const std::string& inputJson, const rapidjson::Document& outputDocument)
{
    if(outputDocument.Parse(inputJson.c_str()).HasParseError())
    {
        std::cerr << "JSON parsing failed: " << rapidjson::GetParseErrorFunc(outputDocument.GetParseError()) << std::endl;
        return false;
    }
    elae 
    {
        return true;
    }
}


// Implementing the build methods 

std::string JSONProcessor::buildHelloMessage()
{
    rapidjson::Document document;
    document.SetObject();
    auto& allocator = document.GetAllocator();


    document.AddMember("status", "success", allocator);
    document.AddMember("message", "Welcome to the C++ server", allocator);

    return serialize(document);
}



std::string JSONProcessor::buildResponse(const std::string& response)
{
    rapidjson::Document document;
    document.SetObject();
    auto& allocator = document.GetAllocator();

    document.AddMember("status", "success", allocator);
    document.AddMember("response", rapidjson::Value(response.c_str(), allocator), allocator);

    return serialize(document);
}




std::string JSONProcessor::buildError(const std::string& errorMessage)
{
    rapidjson::Document document;
    document.setObject();
    auto& allocator = document.GetAllocator();

    document.AddMember("status", "error", allocator);
    document.AddMember("message", rapidjson::Value(errorMessage.c_str(), allocator), allocator);

    return serialize(document);
}



std::string JSONProcessor::serialize(const rapidjson::Document& document)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    document.Accept(writer);

    return buffer.GetString();
    
}