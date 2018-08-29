# README #

This repository contain the "hiss" project written in c++

### Dependencies

Install gtest

      sudo apt-get install libgtest-dev
      cd /usr/src/gtest
      sudo cmake CMakeLists.txt
      sudo make
      sudo cp *.a /usr/lib
      
Install ncurses

      sudo apt-get install ncurses-dev

### Build

      mkdir build
      cd build
      cmake ..
      make
    
### Test

      make test
