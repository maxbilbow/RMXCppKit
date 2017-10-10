cmake_minimum_required(VERSION 3.9)
project(RMXCppKit)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp RMXMaths/types.h RMXMaths/types.cpp RMXMaths/operations.h RMXMaths/RMXMaths.h RMXMaths/operations.cpp)
add_executable(RMXCppKit ${SOURCE_FILES})

#include_directories("RMXKit/headers")

link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})