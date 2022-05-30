cmake_minimum_required(VERSION 3.18.4)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-v -g -O0 -Wall -Wextra -Wpedantic")

set(SOURCES
        project/src/server.cpp)

add_library(lib ${SOURCES})

target_include_directories(lib PUBLIC project/include)
include_directories(include)


add_executable(server.out project/src/main_server.cpp)
target_link_libraries(server.out lib)
