cmake_minimum_required(VERSION 3.18.4)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wpedantic")

find_package(Boost REQUIRED)

set(SOURCES
        src/utils.cpp)

add_library(lib ${SOURCES})

target_include_directories(lib PUBLIC include ${Boost_INCLUDE_DIRS})
target_link_libraries(lib PUBLIC ${Boost_LIBRARIES})
include_directories(include)

add_executable(cient.out src/main_client_tmp)
target_include_directories(client.out PRIVATE ${Boost_INCLUDE_DIRS})

add_executable(server.out src/main_server.cpp)
target_link_libraries(server.out lib)
