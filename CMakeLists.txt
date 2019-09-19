cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(tcpserver LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(tcpserver ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE CHATSERVER_FILES
    ${PROJECT_SOURCE_DIR}/chatserver/*.cpp
    ${PROJECT_SOURCE_DIR}/chatserver/*.h)
add_executable(chatserver ${CHATSERVER_FILES})
