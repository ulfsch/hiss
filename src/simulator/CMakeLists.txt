
include_directories(../model)

set(SOURCE_FILES
        Simulator.cpp
        Simulator.h
        Passenger.cpp
        Passenger.h
        ConstantTraffic.cpp
        ConstantTraffic.h
        CallButtonAlgorithm.cpp
        CallButtonAlgorithm.h
        UpDownButtonAlgorithm.cpp
        UpDownButtonAlgorithm.h)

add_library(simulator ${SOURCE_FILES})
target_link_libraries(simulator Qt4::QtCore)