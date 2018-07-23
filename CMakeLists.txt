cmake_minimum_required(VERSION 3.5.1)
project(mailbridge)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11")

set(CMAKE_CXX_FLAGS_DEBUG "-g -DIS_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

add_compile_options(-Wall -Wextra -Wpedantic -Wno-missing-field-initializers -Wno-unused-parameter)

add_executable(mailbridge src/mailbridge.cpp)