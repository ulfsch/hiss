

set(SOURCE_FILES
        Passenger.cpp
        Passenger.h
        common.h
        Building.cpp
        Building.h
        Elevator.cpp
        Elevator.h
        Floor.cpp
        Floor.h)

add_library(model ${SOURCE_FILES})
