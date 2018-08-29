
include_directories(../model)

set(SOURCE_FILES
        Configuration.cpp
        Configuration.h
        tinyxml2.cpp
        tinyxml2.h)

add_library(cfg ${SOURCE_FILES})
