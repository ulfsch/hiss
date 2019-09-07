
include_directories(../model)

set(SOURCE_FILES
        Algorithm.h
        Simulator.cpp
        Simulator.h
        Passenger.cpp
        Passenger.h
        Stop.cpp
        Stop.h
        ConstantTraffic.cpp
        ConstantTraffic.h
        TrivialAlgorithm.cpp
        TrivialAlgorithm.h
        StandardAlgorithm.cpp
        StandardAlgorithm.h)

add_library(simulator ${SOURCE_FILES})
target_link_libraries(simulator Qt4::QtCore)