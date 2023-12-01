cmake_minimum_required(VERSION 3.5)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

project(fourier)

add_sources(${CMAKE_CURRENT_LIST_DIR}/fourier.cpp)
add_executable(${PROJECT_NAME} fourier.cpp)