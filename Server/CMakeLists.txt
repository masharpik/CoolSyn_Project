cmake_minimum_required(VERSION 3.18.4)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wpedantic")

set(SOURCES
        src/main.cpp
        src/utils.cpp)

add_library(lib ${SOURCES})
target_include_directories(lib PUBLIC include)
include_directories(include)


add_executable(server.out src/main.cpp)
target_link_libraries(server.out lib)
