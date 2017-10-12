cmake_minimum_required(VERSION 3.9)
project(RMXMathsTests)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(MATH_DIR ../../RMXMaths)
set(SOURCE_FILES ${MATH_DIR})

include_directories("${MATH_DIR}")

add_executable(TypeTest typesTest.cpp ${SOURCE_FILES})

