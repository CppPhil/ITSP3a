# ITSP3 Application README
## Prerequisites
- git
- CMake
- GCC (including g++) version 6.3.0 or newer
- Doxygen (if you want to build the documentation)
## Notes
The application will write the data containing the usernames and their corresponding hashes to a file named 'data.bin'.  
If compiled in debug mode the application will generate a debug.log file.  
Note that the log file will contain the passwords entered and should only be used for debugging purposes.  
Note that currently only GNU/Linux based operating systems are supported.  
There are specifically no current plans to support Microsoft Windows operating systems.  
Note that currently only x64 based processors are supported.  
## Dependencies
### bcrypt
#### Installation
navigate to the home directory using  
`
cd ~
`  
Download the bcrypt source code using  
`
git clone --recursive https://github.com/rg3/bcrypt.git
`  
Navigate into the bcrypt directory using  
`
cd ~/bcrypt
`  
Build the bcrypt library using  
`
make
`  
#### Documentation
See the source files at https://github.com/rg3/bcrypt  
### boost
#### Installation
Install the boost libraries using  
`
sudo apt-get -y install libboost-all-dev
`  
Note that this command will very likely install a very outdated version of the boost libraries and will not (properly) build them.  
Therefore only the 'header-only' libraries of the boost libraries may be used.  
Fortunately this is sufficient as of now.  
#### Documentation
See http://www.boost.org/doc/  
### philslib
#### Installation
navigate to the home directory using  
`
cd ~
`  
Download the philslib source code using  
`
git clone https://github.com/CppPhil/philslib.git
`  
Navigate into the philslib directory using  
`
cd ~/philslib
`  
Build the philslib library in debug mode using  
`
bash ./build.sh Debug x64
`  
Build the philslib library in release mode using  
`
bash ./build.sh Release x64
`  
#### Documentation
Documentation can be found as inline documentation in the source files at https://github.com/CppPhil/philslib  
The inline documentation can be used to generate a Doxygen based documentation.  
### Doctest
#### Installation
navigate to the home directory using  
`
cd ~
`  
Download the doctest source code using  
`
git clone https://github.com/onqtam/doctest.git
`  
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
./itsp3a
`  
Note that the application will prompt for keyboard input.  
## Executing the tests
After having built the application the tests can be run using  
`
bash ./test.sh
`  
Note that running the tests can take a long time as many hashes are being calculated.  
(Up to ~30 seconds approximately)
## Cleaning the build directory
If you for some reason want to 'clean' the build directory you can invoke  
`
bash ./clean.sh
`  
to do just that.  
You might want to 'clean' the build directory after having added a new source file in order to make QtCreator recognize the new source file's existence.
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
