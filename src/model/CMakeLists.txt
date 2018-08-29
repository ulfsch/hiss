

set(SOURCE_FILES
        common.h
        Algorithm.h
        Traffic.h
        Passenger.cpp
        Passenger.h
        Direction.cpp
        Direction.h
        Building.cpp
        Building.h
        Elevator.cpp
        Elevator.h
        Floor.cpp
        Floor.h
        Car.cpp
        Car.h)

add_library(model ${SOURCE_FILES})
