cmake_minimum_required(VERSION 3.2)
project(llog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
set(SOURCE_FILES main.cpp src/llog/llog.cpp src/llog/llog.h src/llog/llog_message.cpp src/llog/llog_message.h)

link_libraries(pthread)
add_executable(llog ${SOURCE_FILES})