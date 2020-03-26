
set(SOURCE_FILES
        common.h
        Traffic.h
        Building.cpp
        Building.h
        Elevator.cpp
        Elevator.h
        Floor.cpp
        Floor.h
        Car.cpp
        Car.h
        )

add_library(model ${SOURCE_FILES})
target_link_libraries(model Qt4::QtCore)
