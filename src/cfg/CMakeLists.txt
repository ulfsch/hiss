
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtCore)

include_directories(../model ../simulator)

set(SOURCE_FILES
        Configuration.cpp
        Configuration.h
        tinyxml2.cpp
        tinyxml2.h
        Result.cpp
        Result.h)

add_library(cfg ${SOURCE_FILES})
target_link_libraries(cfg Qt4::QtCore)
