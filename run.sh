#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly prev_dir=$(pwd)

cd $DIR

./build/app/itsp3a

cd $prev_dir

exit 0

