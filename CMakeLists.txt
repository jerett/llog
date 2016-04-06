cmake_minimum_required(VERSION 3.5)
project(llog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp llog.cpp llog.h llog_message.cpp llog_message.h)
add_executable(llog ${SOURCE_FILES})