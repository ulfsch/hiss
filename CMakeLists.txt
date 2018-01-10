cmake_minimum_required(VERSION 2.7)
project(Chiss)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES main.cpp)
add_executable(hiss ${SOURCE_FILES})

add_subdirectory(model)
add_subdirectory(simulator)
add_subdirectory(builder)

enable_testing()
add_subdirectory(test)

target_link_libraries(hiss builder simulator model ncurses)
