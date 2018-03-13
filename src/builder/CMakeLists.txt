
include_directories(../builder)
include_directories(../model)
include_directories(../simulator)

set(SOURCE_FILES
        Factory.cpp
        Factory.h
        tinyxml2.cpp
        tinyxml2.h)

add_library(builder ${SOURCE_FILES})
