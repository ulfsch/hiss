
find_package(Qt4 REQUIRED QtCore)
find_package(Qt4 REQUIRED QtGui)

include_directories(model)
include_directories(simulator)
include_directories(cfg)
include_directories(gui)

add_executable(hiss main.cpp)
target_link_libraries(hiss cfg simulator model ncurses Qt4::QtGui)

add_executable(ghiss main_gui.cpp)
target_link_libraries(ghiss gui cfg simulator model Qt4::QtGui)

add_subdirectory(model)
add_subdirectory(simulator)
add_subdirectory(cfg)
add_subdirectory(gui)
