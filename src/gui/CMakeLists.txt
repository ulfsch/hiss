
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtGui)

include_directories(../model)

set(SOURCE_FILES
        ConfigurationWindow.cpp
        ConfigurationWindow.h
        BuildingWidget.cpp
        BuildingWidget.h
        ElevatorWidget.cpp
        ElevatorWidget.h
        FloorWidget.cpp
        FloorWidget.h)

add_library(gui ${SOURCE_FILES})
target_link_libraries(gui Qt4::QtGui)
