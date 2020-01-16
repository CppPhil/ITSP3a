set(LIBRARY_NAME itsp3a_lib)
file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS include/*.hpp)
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")
target_link_libraries(${LIBRARY_NAME} PUBLIC bcrypt)
target_include_directories(
  ${LIBRARY_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
         ${itsp3a_SOURCE_DIR}/submodules/philslib/include
         ${itsp3a_SOURCE_DIR}/submodules/doctest/doctest)
