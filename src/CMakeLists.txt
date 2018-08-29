
include_directories(cfg)
include_directories(model)
include_directories(simulator)

set(SOURCE_FILES main.cpp)
add_executable(hiss ${SOURCE_FILES})

target_link_libraries(hiss cfg simulator model ncurses)

add_subdirectory(cfg)
add_subdirectory(model)
add_subdirectory(simulator)
