#! /bin/bash
# This script is used to build the project
if [ -d "build" ]; then
    rm -rf build
fi
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make 
