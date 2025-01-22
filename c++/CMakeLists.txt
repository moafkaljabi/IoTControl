cmake_minimum_required(VERSION 3.10)

project(ServerApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable
add_executable(server src/main.cpp src/server.cpp)

# Optionally, you can specify additional flags like optimizations
set_target_properties(server PROPERTIES 
    CXX_FLAGS "-Wall -Wextra -O2")

# Optionally add a linker flag if necessary
# target_link_libraries(server some_library)
