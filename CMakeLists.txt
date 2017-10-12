cmake_minimum_required(VERSION 3.9)
project(RMXCppKit)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})

set(ENGINE_DIR RMXEngine)
set(KIT_DIR RMXKit)
set(MATH_DIR RMXMaths)
set(SOURCE_FILES ${ENGINE_DIR} ${KIT_DIR} ${MATH_DIR})

include_directories("${KIT_DIR}" "${ENGINE_DIR}" "${MATH_DIR}")
#include_directories("${MATH_DIR}")


set(SOURCE_FILES RMXMaths/operations.h RMXMaths/RMXMaths.h RMXMaths/operations.cpp RMXMaths/raw_types.h RMXMaths/raw_types.cpp)
add_executable(RMXCppKit main.cpp ${SOURCE_FILES})

#add_definitions(-DDEBUG_RMX_OBJECT -DDEBUG_MALLOC)
## Engine Tests
add_executable(CameraTest tests/RMXEngine/CameraTest.cpp ${SOURCE_FILES})


## Kit tests
add_executable(ObjectTest tests/RMXKit/ObjectTest.cpp ${KIT_DIR})
add_executable(EventListenerTest tests/RMXKit/EventListenerTest.cpp ${KIT_DIR})


## Maths Tests
add_executable(TypeTest tests/RMXMaths/typesTest.cpp ${SOURCE_FILES})


#add_subdirectory(tests/RMXEngine)
#add_subdirectory(tests/RMXKit)
#add_subdirectory(tests/RMXMaths)
#include_directories("RMXKit/headers")

