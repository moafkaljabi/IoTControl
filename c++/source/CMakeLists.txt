# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TCPServerProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(TCPServer ${SOURCES})

# Link any necessary libraries
# If additional libraries are needed (e.g., pthread), link them here
target_link_libraries(TCPServer pthread)
