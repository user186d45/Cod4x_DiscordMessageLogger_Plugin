cmake_minimum_required(VERSION 3.22)

# Set some basic project attributes
project(Cod4x_DiscordMessageLogger_Plugin VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -Wall -O1 -fvisibility=hidden -mtune=core2")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32 -shared")

set(DPP_ROOT_DIR "/usr/local")
find_package(DPP REQUIRED)

set(SQLITE3_INCLUDE_DIR "/usr/include/i386-linux-gnu")
set(SQLITE3_LIBRARY "/lib/i386-linux-gnu/libsqlite3.so")
include_directories(${SQLITE3_INCLUDE_DIR})
set(SQLite3_LIBRARIES ${SQLITE3_LIBRARY})  # Set the library variable manually

set(PTHREAD_INCLUDE_DIR "/usr/include/i386-linux-gnu")
set(PTHREAD_LIBRARY "/lib/i386-linux-gnu/libpthread.so.0")
include_directories(${PTHREAD_INCLUDE_DIR})
set(PTHREAD_LIBRARIES ${PTHREAD_LIBRARY})

include_directories(libs)
include_directories(includes)

# Include the configuration header in the build
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
    @ONLY
)

add_library(${PROJECT_NAME} SHARED src/Cod4x_DiscordMessageLogger_Plugin.cpp src/MessageLogger.cpp src/DiscordLogger.cpp src/LoggerHandler.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${DPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PTHREAD_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DPP_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE ${DPP_INCLUDE_DIR})


set_target_properties(${PROJECT_NAME} PROPERTIES
	    CXX_STANDARD 20
	    CXX_STANDARD_REQUIRED ON
)
