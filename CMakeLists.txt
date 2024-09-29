cmake_minimum_required(VERSION 3.10)

project(fourier-transformation LANGUAGES CXX)

# Ensure C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find Python and NumPy
find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)

message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_LIBRARIES: ${Python3_LIBRARIES}")
message(STATUS "Python3_NumPy_INCLUDE_DIRS: ${Python3_NumPy_INCLUDE_DIRS}")
message(STATUS "Python3_NumPy_VERSION: ${Python3_NumPy_VERSION}")

# Ensure NumPy is found
if(NOT Python3_NumPy_FOUND)
    message(FATAL_ERROR "NumPy not found! Please make sure NumPy is installed in your Python environment.")
endif()

# Matplotlib for C++ include directory
set(MATPLOTLIB_CPP_DIR "${CMAKE_SOURCE_DIR}/src/matplotlibcpp")

# Source directories
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
set(FOURIER_DIR "${SOURCES_DIR}/fourier")
set(SATELLITE_READER_DIR "${SOURCES_DIR}/satellite_reader")

# Gather source files
file(GLOB_RECURSE SOURCES
    "${SOURCES_DIR}/*.cpp"
    "${FOURIER_DIR}/*.cpp"
    "${SATELLITE_READER_DIR}/*.cpp"
)

# Define executable
add_executable(fourier-transformation ${SOURCES})

# Include directories
target_include_directories(fourier-transformation
    PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
    ${MATPLOTLIB_CPP_DIR}
    ${FOURIER_DIR}
    ${SATELLITE_READER_DIR}
)

# Link libraries
target_link_libraries(fourier-transformation PRIVATE ${Python3_LIBRARIES})

# Copy the entire example folder to the output directory after building
add_custom_command(TARGET fourier-transformation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/example
    $<TARGET_FILE_DIR:fourier-transformation>/example
)

# Copy python311.dll to the output 
if(WIN32)
    add_custom_command(TARGET fourier-transformation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${Python3_RUNTIME_LIBRARY_RELEASE}  # This is where CMake stores the path to python311.dll
        $<TARGET_FILE_DIR:fourier-transformation>/python311.dll
    )
endif()

# Optional: Enable Unicode definitions (if necessary)
target_compile_definitions(fourier-transformation PRIVATE UNICODE _UNICODE)
