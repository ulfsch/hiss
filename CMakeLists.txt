cmake_minimum_required(VERSION 3.8)
project(Chiss)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.cpp)
add_executable(hiss ${SOURCE_FILES})

add_subdirectory(model)
add_subdirectory(simulator)
add_subdirectory(gtest-1.7.0)

enable_testing()
add_subdirectory(test)

target_link_libraries(hiss simulator model ncurses)
