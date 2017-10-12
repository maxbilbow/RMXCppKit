cmake_minimum_required(VERSION 3.9)
project(RMXKitTests)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories("../../RMXKit")

add_definitions(-DDEBUG_RMX_OBJECT -DDEBUG_MALLOC)
add_executable(ObjectTest ObjectTest.cpp ../../RMXKit/Object.h ../../RMXKit/Object.cpp)
#add_executable(EventListenerTest EventListenerTest.cpp ${SOURCE_FILES})


#add_executable(Tests.h test2.cpp ${SOURCE_FILES})

