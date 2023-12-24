cmake_minimum_required(VERSION 3.8)

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

### Python3
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        ef0383f1315d32e0156335e10b82e90b334f6d9f
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})

# Fourier Transformation Library
set(FOURIER_DIR "${SOURCES_DIR}/fourier")
include_directories(${FOURIER_DIR})

add_executable(fourier-transformation ${SOURCES})
target_link_libraries(fourier-transformation PRIVATE Python3::Python)
target_link_libraries(fourier-transformation PRIVATE Python3::NumPy)
