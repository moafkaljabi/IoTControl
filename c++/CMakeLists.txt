cmake_minimum_required(VERSION 3.10)
project(ServerApp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/json)
include_directories(${CMAKE_SOURCE_DIR}/include/Mqtt)

# RapidJSON (header-only)
find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h)
if (RAPIDJSON_INCLUDE_DIR)
    include_directories(${RAPIDJSON_INCLUDE_DIR})
else()
    message(FATAL_ERROR "RapidJSON not found!")
endif()

# Manually locate Paho MQTT libraries (adjust paths as needed)
find_library(PAHO_MQTT_CPP_LIB paho-mqttpp3)
find_library(PAHO_MQTT_C_LIB paho-mqtt3as)

if (NOT PAHO_MQTT_CPP_LIB OR NOT PAHO_MQTT_C_LIB)
    message(FATAL_ERROR "Paho MQTT C/C++ libraries not found!")
endif()

# Source files
file(GLOB SOURCES 
    src/*.cpp
    src/json/*.cpp
    src/mqtt/*.cpp
    main.cpp
)

# Executable
add_executable(server ${SOURCES})

# Link manually found libraries
target_link_libraries(server
    ${PAHO_MQTT_CPP_LIB}
    ${PAHO_MQTT_C_LIB}
)

target_compile_options(server PRIVATE -Wall -Wextra -O2)
