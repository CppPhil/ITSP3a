# ITSP3 Application README

## Created in late 2017

## Prerequisites
- git
- CMake
- GCC (including g++)
- Doxygen (if you want to build the documentation)

## Notes
The application will write the data containing the usernames and their corresponding hashes to a file named 'data.bin'.  
If compiled in debug mode the application will generate a debug.log file.  
Note that the log file will contain the passwords entered and should only be used for debugging purposes.  
Note that currently only GNU/Linux based operating systems are supported.  
There are specifically no current plans to support Microsoft Windows operating systems.  
Note that currently only x64 based processors are supported.  

## Cloning 
The repository must be cloned recursively to fetch the submodules.  
`git clone https://github.com/CppPhil/ITSP3a.git --recursive` for instance.  

## Dependencies
### bcrypt
#### Documentation
See the source files at https://github.com/rg3/bcrypt  

### philslib
#### Documentation
Documentation can be found as inline documentation in the source files at https://github.com/CppPhil/philslib  
The inline documentation can be used to generate a Doxygen based documentation.  

### Doctest
#### Documentation
For documentation of doctest refer to the github page: https://github.com/onqtam/doctest#documentation  

## Building
Build the application in debug mode (not recommended, unless you require the debug.log file for debugging purposes) using  
`
bash ./build.sh Debug
`  
Or build the application in release mode (recommended) using  
`
bash ./build.sh Release
`  

## Running
After having built the application it can be run using  
`
bash ./run.sh
`  
Note that the application will prompt for keyboard input.  

## Executing the tests
After having built the application the tests can be run using  
`
bash ./test.sh
`  
Note that running the tests can take a long time as many hashes are being calculated.  
(Up to ~30 seconds approximately)

## Generating the documentation
To generate the documentation run  
`
doxygen Doxyfile
`  
  
To view the documentation open the index.html file.  
If using Mozilla Firefox the command would be:  
`
firefox ./docs/html/index.html &
`  
