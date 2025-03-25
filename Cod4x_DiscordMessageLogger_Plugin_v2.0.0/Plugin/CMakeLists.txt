set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i386)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32 -g -shared")

set(PTHREAD_INCLUDE_DIR "/usr/include/i386-linux-gnu")
set(PTHREAD_LIBRARY "/lib/i386-linux-gnu/libpthread.so.0")
include_directories(${PTHREAD_INCLUDE_DIR})
set(PTHREAD_LIBRARIES ${PTHREAD_LIBRARY})

# Include the configuration header in the build
configure_file(version.h.in version.h)

include_directories(libs includes)

add_library(${PROJECT_NAME}_Plugin SHARED src/Plugin.cpp src/Queue.cpp)

target_link_libraries(${PROJECT_NAME}_Plugin PRIVATE ${PTHREAD_LIBRARIES})

target_include_directories(${PROJECT_NAME}_Plugin PUBLIC "${PROJECT_BINARY_DIR}")