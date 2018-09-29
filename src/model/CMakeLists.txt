
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtCore)

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
target_link_libraries(model Qt4::QtCore)
