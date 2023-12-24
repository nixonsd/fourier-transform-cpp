cmake_minimum_required(VERSION 3.8)

project(fourier-transformation LANGUAGES CXX)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(EXECUTABLE_OUTPUT_PATH bin)

set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES
  "${SOURCES_DIR}/*.cpp"
  "${SOURCES_DIR}/*.hpp"
)

include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Fourier Transformation Library
set(FOURIER_DIR "${SOURCES_DIR}/fourier")
include_directories(${FOURIER_DIR})

add_executable(fourier-transformation ${SOURCES})
target_link_libraries(fourier-transformation PUBLIC matplot)

# Copy example file
configure_file(${SOURCES_DIR}/example/Sample_Signal.txt ${CMAKE_CURRENT_BINARY_DIR}/bin/Sample_Signal.txt COPYONLY)