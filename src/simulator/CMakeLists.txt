
include_directories(../model)
include_directories(../cfg)

set(SOURCE_FILES
        Simulator.cpp
        Simulator.h
        ../model/Algorithm.h
        ../model/Traffic.h
        ConstantTraffic.cpp
        ConstantTraffic.h
        CallButtonAlgorithm.cpp
        CallButtonAlgorithm.h
        UpDownButtonAlgorithm.cpp
        UpDownButtonAlgorithm.h)

add_library(simulator ${SOURCE_FILES})
