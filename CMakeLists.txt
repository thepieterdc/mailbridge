cmake_minimum_required(VERSION 3.5.1)
project(mailbridge VERSION "2.0.0")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS_DEBUG "-g -DIS_DEBUG -fdiagnostics-show-option")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")

add_definitions(-DMAILBRIDGE_VERSION="${PROJECT_VERSION}")

find_package(CURL REQUIRED)
find_package(Json REQUIRED)

file(GLOB servers_SRC
    "src/servers/*.h"
    "src/servers/*.cpp")

file(GLOB util_SRC
        "src/util/*.h"
        "src/util/*.cpp")

add_compile_options(-Wall -Wextra -Wpedantic -Wno-missing-field-initializers -Wno-unused-parameter)

add_executable(mailbridge src/main.cpp ${servers_SRC} ${util_SRC} src/messages/smtp_message.h src/servers/threads/smtp_thread.h)
target_link_libraries(mailbridge curl pthread)

include_directories(${JSON_INCLUDE_DIRS})