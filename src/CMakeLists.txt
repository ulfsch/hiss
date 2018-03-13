
include_directories(builder)
include_directories(model)
include_directories(simulator)

set(SOURCE_FILES main.cpp)
add_executable(hiss ${SOURCE_FILES})

target_link_libraries(hiss builder simulator model ncurses)

add_subdirectory(builder)
add_subdirectory(model)
add_subdirectory(simulator)
