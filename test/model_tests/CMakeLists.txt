
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(runModelTests
        passenger_check.cpp
        elevator_check.cpp)

find_package(Qt4 REQUIRED QtCore)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../../src/model)

target_link_libraries(runModelTests model gtest gtest_main Qt4::QtCore pthread)

add_test(runModelTests runModelTests)
