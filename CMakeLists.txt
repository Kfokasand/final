cmake_minimum_required (VERSION 2.6)
project(neurosis)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCEDIR}/include  ${gtest_SOURCE_DIR})

add_executable (neurosis neuron.cpp simulation.cpp main.cpp network.cpp)
add_executable (unittest unittest.cpp neuron.cpp simulation.cpp network.cpp)

target_link_libraries(unittest gtest gtest_main)
add_test(unittest unittest)
