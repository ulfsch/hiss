
include_directories(../model)

set(SOURCE_FILES
        MainWindow.cpp
        MainWindow.h
        BuildingWidget.cpp
        BuildingWidget.h
        ElevatorWidget.cpp
        ElevatorWidget.h
        FloorWidget.cpp
        FloorWidget.h)

add_library(gui ${SOURCE_FILES})
target_link_libraries(gui Qt4::QtGui)
