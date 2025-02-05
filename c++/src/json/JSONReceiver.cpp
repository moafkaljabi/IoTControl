
#include "JSONReceiver.h"



void JSONReceiver::parseJSON(const std::string& jsonData) 
{
    
    rapidjson::Document doc;

    if (doc.Parse(jsonData.c_str()).HasParseError())
    {
        std::cerr << "Failed to parse JSON from client: " << doc.GetParseError() << std::endl;
        return;
    }

    // Use PrettyWriter to format JSON output
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::cout << "Received JSON (Pretty-Printed):\n" << buffer.GetString() << std::endl;
}
