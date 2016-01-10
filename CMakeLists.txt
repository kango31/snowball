cmake_minimum_required(VERSION 2.8)
SET(CMAKE_INSTALL_PREFIX /usr/local)
project(snowball)
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

#===============================================================================
# Compiler flags
#===============================================================================

#Use C++11
set( CMAKE_CXX_FLAGS  "-std=c++11" )

#===============================================================================
# snowball lib
#===============================================================================

file(
    GLOB_RECURSE
    snowball_src
    src/*
    )

add_library(
    snowball STATIC
    ${snowball_src}
    )

#===============================================================================
# Unit tests
#===============================================================================

file(
    GLOB_RECURSE
    snowball_test
    tests/*
    src/*
    )

add_executable(
    snowball_test
    ${snowball_test}
    )
    
target_include_directories(
    snowball_test
    PUBLIC
    src/subprocess
)

add_custom_target(
    test
    bin/snowball_test -s -d yes
    DEPENDS bin/snowball_test
    )
    
#===============================================================================
# Documentation
#===============================================================================

find_package(Doxygen)
if (DOXYGEN_FOUND)
    MESSAGE("Doxygen found: ${DOXYGEN_EXECUTABLE}")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
        @ONLY
        )
    add_custom_target(
        doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

#===============================================================================
# Installation
#===============================================================================

#install(TARGETS snowball
#        RUNTIME DESTINATION bin)
