
include_directories(model)
include_directories(simulator)
include_directories(cfg)
include_directories(gui)

add_subdirectory(model)
add_subdirectory(simulator)
add_subdirectory(cfg)
add_subdirectory(gui)

add_executable(hiss main.cpp)
target_link_libraries(hiss cfg simulator model ncurses)

add_executable(ghiss main_gui.cpp)
target_link_libraries(ghiss gui cfg simulator model)
