cmake_minimum_required(VERSION 2.7)
project(Chiss)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_subdirectory(src)
enable_testing()
add_subdirectory(test)

