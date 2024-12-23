#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <bits/this_thread_sleep.h>

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
