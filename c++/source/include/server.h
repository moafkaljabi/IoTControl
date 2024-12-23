#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <fstream>
#include <string>
#include "main.h"

int server();

class Control {
public:
    Control(int gpioPin);
    ~Control();
    void blinkLED(int delayMs);

private:
    int m_gpioPin;
    std::string gpioBasePath;
    std::string gpioValuePath;
};

#endif // CONTROL_H
