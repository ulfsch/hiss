
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../../src/model)

add_executable(runModelTests
        passenger_check.cpp
        elevator_check.cpp)
target_link_libraries(runModelTests model gtest gtest_main Qt4::QtCore pthread)

add_test(runModelTests runModelTests)
