cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(itsp3a)

file(GLOB_RECURSE BCRYPT_SOURCES CONFIGURE_DEPENDS submodules/bcrypt/*.c
     submodules/bcrypt/*.h)
add_library(bcrypt SHARED ${BCRYPT_SOURCES})
target_include_directories(bcrypt PUBLIC submodules/bcrypt)

add_subdirectory(lib)
add_subdirectory(app)

# by default password checks from aufgabe 3.c) are enabled.
add_definitions(-DENABLE_PW_CHECKS)

enable_testing()
set(UNIT_TEST_NAME unittest)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/src/*.cpp)
add_executable(${UNIT_TEST_NAME} "${TEST_SOURCES}")
add_test(Unittest ${UNIT_TEST_NAME})
target_link_libraries(${UNIT_TEST_NAME} PRIVATE itsp3a_lib)
