
find_package(Qt4 REQUIRED QtCore)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../../src/model)
include_directories(../../src/simulator)

add_executable(runSimulatorTests
        up_down_algorithm_check.cpp)

target_link_libraries(runSimulatorTests simulator model gtest gtest_main Qt4::QtCore pthread)

add_test(runSimulatorTests runSimulatorTests)

