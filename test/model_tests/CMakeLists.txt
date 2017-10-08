include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runModelTests
        passenger_check.cpp
        elevator_check.cpp)

target_link_libraries(runModelTests model gtest gtest_main)

add_test(runModelTests runModelTests)

