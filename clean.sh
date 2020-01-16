#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

rm -f $DIR/data.bin
rm -f $DIR/debug.log

