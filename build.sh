#! /bin/bash
# This script is used to build the project
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make 
