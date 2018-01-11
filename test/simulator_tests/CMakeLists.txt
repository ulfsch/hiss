include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSimulatorTests
        up_down_algorithm_check.cpp)

target_link_libraries(runSimulatorTests simulator model gtest gtest_main pthread)

add_test(runSimulatorTests runSimulatorTests)

