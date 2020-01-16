# GENERAL
cmake_minimum_required(VERSION 3.1)

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# warning flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
endif()

# Optimization flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNDEBUG)
else ()
    add_definitions(-DDEBUG_MODE)
endif()

# declare project
project(itsp3a)

# include paths
include_directories(${CMAKE_BINARY_DIR}/../submodules/bcrypt)
include_directories(${CMAKE_BINARY_DIR}/../submodules/doctest/doctest)
include_directories(${CMAKE_BINARY_DIR}/../submodules/philslib/include)

# STATICALLY LINKED LIBRARY
set(LIBRARY_NAME itsp3a_lib)

file(GLOB LIB_HEADERS
     include/*.hpp)
     
file(GLOB LIB_SOURCES
     src/*.cpp)
     
add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")

target_link_libraries(${LIBRARY_NAME} ${CMAKE_BINARY_DIR}/../submodules/bcrypt/bcrypt.a)

# APPLICATION
file(GLOB APPLICATION_SOURCE_FILES
     ./*.cpp)

add_executable(${PROJECT_NAME} "${LIB_HEADERS}" "${APPLICATION_SOURCE_FILES}")
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})
target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/../submodules/bcrypt/bcrypt.a)

# by default password checks from aufgabe 3.c) are enabled.
add_definitions(-DENABLE_PW_CHECKS)

# TEST
enable_testing()

set(UNIT_TEST_NAME unittest)
     
file(GLOB TEST_SOURCES
     test/src/*.cpp)
     
add_executable(${UNIT_TEST_NAME}
    "${TEST_SOURCES}"
    "${LIB_HEADERS}")
    
add_test(Unittest ${UNIT_TEST_NAME})

target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})    
target_link_libraries(${UNIT_TEST_NAME} ${CMAKE_BINARY_DIR}/../submodules/bcrypt/bcrypt.a)
