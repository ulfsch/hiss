include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runModelTests passenger_check.cpp elevator_check.cpp)

target_link_libraries(runModelTests gtest gtest_main)
target_link_libraries(runModelTests model)

add_test(test runModelTests)

