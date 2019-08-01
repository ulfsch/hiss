
include_directories(../model ../simulator)

set(SOURCE_FILES
        Configuration.cpp
        Configuration.h
        Result.cpp
        Result.h)

add_library(cfg ${SOURCE_FILES})
target_link_libraries(cfg Qt4::QtCore)
