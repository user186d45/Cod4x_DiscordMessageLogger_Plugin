list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i386)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared")

set(DPP_ROOT_DIR "/usr/local")
find_package(DPP REQUIRED)

set(PTHREAD_INCLUDE_DIR "/usr/include/i386-linux-gnu")
set(PTHREAD_LIBRARY "/lib/i386-linux-gnu/libpthread.so.0")
include_directories(${PTHREAD_INCLUDE_DIR})
set(PTHREAD_LIBRARIES ${PTHREAD_LIBRARY})

include_directories("/usr/include")

# This project will output an executable file
add_executable(${PROJECT_NAME}_Server src/Server.cpp src/DiscordBot.cpp src/Queue.cpp src/Signal.cpp src/Thread.cpp src/JSON.cpp)

# Create a simple configuration header
configure_file(version.h.in version.h)

include_directories(includes)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME}_Server PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME}_Server PRIVATE ${DPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_Server PRIVATE ${PTHREAD_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_Server PRIVATE cjson)
