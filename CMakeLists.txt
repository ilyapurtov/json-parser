cmake_minimum_required(VERSION 4.0)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SOURCES src/*.cpp)
add_library(mylib ${SOURCES})

add_executable(json_parser ${SOURCES})

file(GLOB TEST_SOURCES test/*.cpp)
add_executable(json_parser_tests ${TEST_SOURCES})
target_link_libraries(json_parser_tests mylib gtest_main)
target_include_directories(json_parser_tests PRIVATE src)

include(GoogleTest)
gtest_discover_tests(json_parser)