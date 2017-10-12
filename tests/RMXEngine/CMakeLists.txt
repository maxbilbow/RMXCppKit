cmake_minimum_required(VERSION 3.9)
project(RMXEngineTests)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(ENGINE_DIR ../../RMXEngine)
set(KIT_DIR ../../RMXKit)
set(MATH_DIR ../../RMXMaths)
set(SOURCE_FILES ${ENGINE_DIR} ${KIT_DIR} ${MATH_DIR})

include_directories("${KIT_DIR}" "${ENGINE_DIR}" "${MATH_DIR}")

add_executable(CameraTest CameraTest.cpp ${SOURCE_FILES})

#include_directories("../../RMXEngine/")

link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})