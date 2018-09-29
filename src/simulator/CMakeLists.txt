
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtCore)

include_directories(../model)

set(SOURCE_FILES
        Simulator.cpp
        Simulator.h
        ConstantTraffic.cpp
        ConstantTraffic.h
        CallButtonAlgorithm.cpp
        CallButtonAlgorithm.h
        UpDownButtonAlgorithm.cpp
        UpDownButtonAlgorithm.h)

add_library(simulator ${SOURCE_FILES})
target_link_libraries(simulator Qt4::QtCore)