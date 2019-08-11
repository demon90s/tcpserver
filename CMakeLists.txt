cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(tcpserver LANGUAGES CXX)

add_executable(tcpserver ${PROJECT_SOURCE_DIR}/src/main.cpp)
