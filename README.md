# README #

### Build

    git clone git@bitbucket.org:ulfsch/chiss.git
    cd chiss
    mkdir build
    cd build
    cmake ..
    make

### Dependencies

ncurses

    sudo apt-get install libncurses5-dev

gtest

    cd chiss
    ln -s ~/src/gtest-1,7,0
    
### Tests

    make test