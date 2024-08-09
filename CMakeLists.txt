cmake_minimum_required(VERSION 3.10)

# Set the project name and the C++ standard
project(RBTreeProject)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the paths to the source files
set(SOURCES
    code/RBTree.cpp
    test/test.cpp
)

# Specify the include directories
include_directories(${CMAKE_SOURCE_DIR}/code)

# Create an executable
add_executable(rbtree ${SOURCES})

# Enable debugging information and disable optimizations
set_target_properties(rbtree PROPERTIES
    COMPILE_FLAGS "-g -O0 -fno-omit-frame-pointer"
)