

set(SOURCE_FILES
        Simulator.cpp
        Simulator.h
        Algorithm.h
        Traffic.h
        ConstantTraffic.cpp
        ConstantTraffic.h
        CallButtonAlgorithm.cpp
        CallButtonAlgorithm.h)

add_library(simulator ${SOURCE_FILES})
