cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(tcpserver LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(tcpserver ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(chatserver ${PROJECT_SOURCE_DIR}/chatserver/chatserver.cpp)
