cmake_minimum_required(VERSION 3.8)

project(fourier-transformation LANGUAGES CXX)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(EXECUTABLE_OUTPUT_PATH bin)

# Find Python and NumPy
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Manually set the NumPy include directory
set(NUMPY_INCLUDE_DIR "/path/to/numpy/include")  # Replace with the actual path obtained above
include_directories(${NUMPY_INCLUDE_DIR})

# Include directories for Matplotlib for C++
include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

# Set Source Dir variable
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")

# Find the Matplotlib for C++ header (matplotlibcpp.h)
set(MATPLOTLIB_CPP_DIR "${SOURCES_DIR}/matplotlibcpp")
include_directories(${MATPLOTLIB_CPP_DIR})

# Fourier Transformation Library
set(FOURIER_DIR "${SOURCES_DIR}/fourier")
include_directories(${FOURIER_DIR})

file(GLOB_RECURSE SOURCES
    "${SOURCES_DIR}/*.cpp"
    "${SOURCES_DIR}/*.hpp"
    "${SOURCES_DIR}/*.h"
    "${FOURIER_DIR}/*.cpp"
    "${FOURIER_DIR}/*.hpp"
    "${FOURIER_DIR}/*.h"
    "${MATPLOTLIB_CPP_DIR}/*.h"
    "${MATPLOTLIB_CPP_DIR}/*.cpp"
)

add_executable(fourier-transformation ${SOURCES})

# Link against Python libraries
target_link_libraries(fourier-transformation ${Python3_LIBRARIES})

# Set output directories for the build artifacts
set_target_properties(fourier-transformation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Copy example file
configure_file(
    ${CMAKE_SOURCE_DIR}/example/Sample_Signal.txt 
    ${CMAKE_CURRENT_BINARY_DIR}/bin/example/Sample_Signal.txt 
    COPYONLY
)