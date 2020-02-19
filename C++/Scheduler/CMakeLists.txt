cmake_minimum_required(VERSION 2.8.4)
project(Scheduler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    schema/*.cpp
    test/*.cpp)
add_executable(Scheduler ${SOURCE_FILES})