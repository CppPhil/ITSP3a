#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Check the amount of command line parameters
if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Enter Debug or Release for the first parameter."
    exit 1
fi

readonly prev_dir=$(pwd)

cd $DIR

rm -rf ./build
mkdir ./build
cd ./build

# Generate the platform specific build scripts
if [ "$1" == "Debug" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    
    # Build the project
    cmake --build .
   
    cd $prev_dir
    exit 0
fi

if [ "$1" == "Release" ]; then
    cmake -DCMAKE_BUILD_TYPE=Release ..
    
    # Build the project
    cmake --build .
       
    cd $prev_dir
    exit 0
fi

cd $prev_dir
exit 1

