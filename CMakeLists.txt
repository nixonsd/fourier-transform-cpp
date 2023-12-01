cmake_minimum_required(VERSION 3.5)

project(fourier-transformation LANGUAGES CXX)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES
  "${SOURCES_DIR}/*.cpp"
  "${SOURCES_DIR}/*.hpp"
)

# Fourier Transformation Library
set(FOURIER_DIR "${SOURCES_DIR}/fourier")
include_directories(${FOURIER_DIR})

add_executable(fourier-transformation ${SOURCES})
