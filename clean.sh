#!/bin/bash
# Small script to delete garbage

rm ./CMakeCache.txt      # delete CMake cache to force a (somewhat) proper rebuild
rm ./CMakeLists.txt.user # delete .user file generated by QtCreator to make it 
                         # recognize new source files.
rm ./itsp3a              # delete the application executable 
rm ./data.bin            # delete the binary data containing the users and their
                         # login hashes.
rm ./debug.log           # delete the debug log file.
rm ./unittest            # delete the unittest executable
rm ./libitsp3a_lib.a     # delete statically linked application library
rm ./*.bin               # delete any .bin files still there

