cmake_minimum_required(VERSION 4.0)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(json_parser main.cpp
        JSON.cpp
        JSON.h
        parser.cpp
        parser.h
        exceptions.h)
