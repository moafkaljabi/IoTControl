cmake_minimum_required(VERSION 3.10)

project(ServerApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)  # Includes the 'include' directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include/json)  # Includes the 'include/json' directory

# Find all source files in src and src/json directories
file(GLOB SOURCES 
    "src/*.cpp"                # All .cpp files in the 'src' directory
    "src/json/*.cpp"           # All .cpp files in the 'src/json' directory
)

# Add executable with all source files
add_executable(server ${SOURCES})

# Set compiler flags (warnings, optimizations)
set_target_properties(server PROPERTIES 
    CXX_FLAGS "-Wall -Wextra -O2")

# Optionally add a linker flag if necessary
# target_link_libraries(server some_library)
