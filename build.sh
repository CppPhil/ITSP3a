#!/bin/bash

# Check the amount of command line parameters
if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Enter Debug or Release for the first parameter."
    exit 1
fi

# Clean the project directory
bash ./clean.sh

# Generate the platform specific build scripts
if [ "$1" == "Debug" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug .
    
    # Build the project
    cmake --build .
    
    exit 0
fi

if [ "$1" == "Release" ]; then
    cmake -DCMAKE_BUILD_TYPE=Release .
    
    # Build the project
    cmake --build .
    
    exit 0
fi

exit 1

