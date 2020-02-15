
set(SOURCE_FILES
        common.h
        Traffic.h
        Direction.cpp
        Direction.h
        Building.cpp
        Building.h
        Elevator.cpp
        Elevator.h
        Floor.cpp
        Floor.h
        )

add_library(model ${SOURCE_FILES})
target_link_libraries(model Qt4::QtCore)
