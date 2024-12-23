#include "control.h"


Control::Control(int gpioPin) : m_gpioPin(gpioPin) {
    gpioBasePath = "/sys/class/gpio/gpio" + std::to_string(m_gpioPin) + "/";
    gpioValuePath = gpioBasePath + "value";

    // Export GPIO pin
    std::ofstream exportFile("/sys/class/gpio/export");
    if (exportFile.is_open()) {
        exportFile << m_gpioPin;
        exportFile.close();
    } else {
        std::cerr << "Failed to export GPIO pin" << std::endl;
        exit(1);
    }

    // Set GPIO direction to output
    std::ofstream directionFile(gpioBasePath + "direction");
    if (directionFile.is_open()) {
        directionFile << "out";
        directionFile.close();
    } else {
        std::cerr << "Failed to set GPIO direction" << std::endl;
        exit(1);
    }
}

Control::~Control() {
    // Unexport GPIO pin
    std::ofstream unexportFile("/sys/class/gpio/unexport");
    if (unexportFile.is_open()) {
        unexportFile << m_gpioPin;
        unexportFile.close();
    }
}

void Control::blinkLED(int delayMs) {
    std::ofstream valueFile(gpioValuePath);
    if (valueFile.is_open()) {
        // Set GPIO high
        valueFile << "1";
        valueFile.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

        valueFile.open(gpioValuePath);
        // Set GPIO low
        valueFile << "0";
        valueFile.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    } else {
        std::cerr << "Failed to control GPIO" << std::endl;
        exit(1);
    }
}
