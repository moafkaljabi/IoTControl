/*


2025


*/


#pragma once 

#include <memory>
#include "IClientDataProcessor.h"


class IClientDataProcessorFactory {

public:
    virtual ~IClientDataProcessorFactory() = default;
    virtual std::unique_ptr<IClientDataProcessor> createProcessor() = 0;


};