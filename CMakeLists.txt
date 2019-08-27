cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(tcpserver LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
#set(CMAKE_CXX_COMPILER "clang++")

add_executable(rawserver ${PROJECT_SOURCE_DIR}/rawserver/rawserver.cpp)

add_executable(client ${PROJECT_SOURCE_DIR}/client/client.cpp)

file(GLOB_RECURSE QUOTESERVER_FILES
    ${PROJECT_SOURCE_DIR}/quoteserver/*.cpp
    ${PROJECT_SOURCE_DIR}/quoteserver/*.h)
add_executable(quoteserver ${QUOTESERVER_FILES})

file(GLOB_RECURSE CHATSERVER_FILES
    ${PROJECT_SOURCE_DIR}/chatserver/*.cpp
    ${PROJECT_SOURCE_DIR}/chatserver/*.h)
add_executable(chatserver ${CHATSERVER_FILES})
