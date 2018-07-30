cmake_minimum_required(VERSION 3.5.1)
project(mailbridge)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS_DEBUG "-g -DIS_DEBUG -fdiagnostics-show-option")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

file(GLOB util_SRC
        "src/util/*.h"
        "src/util/*.cpp")

add_compile_options(-Wall -Wextra -Wpedantic -Wno-missing-field-initializers -Wno-unused-parameter)

add_executable(mailbridge src/mailbridge.cpp ${util_SRC})
target_link_libraries(mailbridge pthread)