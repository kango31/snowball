cmake_minimum_required(VERSION 2.8.12)
SET(CMAKE_INSTALL_PREFIX /usr/local)
project(snowball)
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

#===============================================================================
# Compiler flags
#===============================================================================

#Use C++11
set(CMAKE_CXX_FLAGS  "-std=c++11" )
#Set debug flags
#These debug flags are used when invoking CMake this way:
#cmake -DCMAKE_BUILD_TYPE=Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

#===============================================================================
# Dependencies
#===============================================================================

#Boost locale
find_package(Boost OPTIONAL_COMPONENTS locale)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DSNOWBALL_WITH_BOOST_LOCALE)
endif (Boost_FOUND)

#===============================================================================
# snowball lib
#===============================================================================

#Manage version number
set(SNOWBALL_VERSION_MAJOR 0)
set(SNOWBALL_VERSION_MINOR 1)
set(SNOWBALL_VERSION_PATCH 0)
add_definitions(-DSNOWBALL_VERSION_MAJOR=${SNOWBALL_VERSION_MAJOR})
add_definitions(-DSNOWBALL_VERSION_MINOR=${SNOWBALL_VERSION_MINOR})
add_definitions(-DSNOWBALL_VERSION_PATCH=${SNOWBALL_VERSION_PATCH})

#Get all source files
file(
    GLOB_RECURSE
    snowball_src
    src/*
    )

#Create library
add_library(
    snowball STATIC
    ${snowball_src}
    )
    
target_include_directories(
    snowball
    PUBLIC
    src/
)

if(Boost_FOUND)
    target_link_libraries(snowball ${Boost_LIBRARIES})
endif(Boost_FOUND)

#===============================================================================
# Unit tests
#===============================================================================

#Get tests source files
file(
    GLOB_RECURSE
    snowball_test
    tests/*
    )

add_executable(
    snowball_test
    ${snowball_test}
    )
    
target_include_directories(
    snowball_test
    PUBLIC
    src/
    catch/
)

if (Boost_FOUND)
    target_link_libraries(snowball ${Boost_LIBRARIES})
endif (Boost_FOUND)

target_link_libraries(snowball_test snowball)

add_custom_target(
    test
    #run verbose
    bin/snowball_test -s -d yes
    #stops at first error
    #bin/snowball_test -a
    #bin/snowball_test -s string version
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
