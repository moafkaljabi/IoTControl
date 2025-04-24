/*


2025

This class is intended to help with the seperation of concerns.

IClientDataProcessor.h

*/


#pragma once 

#include <string>


class IClientDataProcessor {

public:


    ~IClientDataProcessor() = default;

    virtual std::string process(const std::string rawData) = 0;


};