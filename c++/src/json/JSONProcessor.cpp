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