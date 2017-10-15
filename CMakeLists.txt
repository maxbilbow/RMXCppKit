cmake_minimum_required(VERSION 3.9)
project(RMXCppKit)



set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})

set(ENGINE_DIR RMXEngine)
set(KIT_DIR RMXKit)
set(MATH_DIR RMXMaths)
set(SOURCE_FILES ${ENGINE_DIR} ${KIT_DIR} ${MATH_DIR})

include_directories("${KIT_DIR}" "${ENGINE_DIR}" "${MATH_DIR}")
#include_directories("${MATH_DIR}")



#add_executable(RMXCppKit main.cpp ${SOURCE_FILES})

#add_definitions(-DDEBUG_RMX_OBJECT -DDEBUG_MALLOC)
## Engine Tests
#add_executable(CameraTest tests/RMXEngine/CameraTest.cpp ${SOURCE_FILES})


set(RMX_KIT )
## Kit tests
add_executable(ObjectTest tests/RMXKit/ObjectTest.cpp ${KIT_DIR}/Object.h ${KIT_DIR}/Object.cpp)
add_executable(EventListenerTest tests/RMXKit/EventListenerTest.cpp
        ${KIT_DIR}/EventListener.h ${KIT_DIR}/EventListener.cpp
        ${KIT_DIR}/NotificationCenter.h ${KIT_DIR}/NotificationCenter.cpp
        ${KIT_DIR}/Object.h ${KIT_DIR}/Object.cpp)


## Maths Tests
set(MATH_KIT ${MATH_DIR}/operations.h ${MATH_DIR}/RMXMaths.h ${MATH_DIR}/operations.cpp ${MATH_DIR}/raw_types.h ${MATH_DIR}/raw_types.cpp)
add_executable(TypeTest tests/RMXMaths/typesTest.cpp ${MATH_KIT})


#add_subdirectory(tests/RMXEngine)
#add_subdirectory(tests/RMXKit)
#add_subdirectory(tests/RMXMaths)
#include_directories("RMXKit/headers")

