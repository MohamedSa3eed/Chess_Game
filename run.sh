#! /bin/bash
# This script is used to run the project
if [ -d build ]; then
    cd build
    make
    ./Chess
else
    echo "The program doesn't exist. Please build the project first."
fi
