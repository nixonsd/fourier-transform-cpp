# Installation
## Prerequisites
1. Install CMake
Ensure CMake is installed on your system. You can download it from [here](https://cmake.org/download/).

2. Install Python 3
Ensure Python 3 is installed on your system. You can download it from [here](https://www.python.org/downloads/).

3. Install Required Python Packages
Install the necessary Python packages using pip:
```bash
pip install numpy matplotlib
```
Note: Make sure that the Python environment variables are correctly set up.

# Building the Project
## Building on Linux/MacOS
To build the project on Linux or macOS, follow these steps:

```bash
cmake .
cmake --build . --target all
```
## Building on Windows
To build the project on Windows, use the following commands:

```bash
cmake -G "Visual Studio 17 2022" -A Win32 # example, you may configure as you see fit
cmake --build . --target all
```
Alternatively, you can use the commands as before.

For more details, refer to the [CMake documentation for Visual Studio 17 2022](https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html#).

# Debugging
## Windows
Visual Studio: Use Visual Studio on Windows for debugging.

## Cross-Platform
Visual Studio Code: You can also use Visual Studio Code with the provided pre-configurations. Make sure to update the paths to the corresponding executables as needed in your environment.
