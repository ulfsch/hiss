cmake_minimum_required(VERSION 3.5)
project(Chiss   LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtCore QtGui)

add_subdirectory(src)


enable_testing()
add_subdirectory(test)

