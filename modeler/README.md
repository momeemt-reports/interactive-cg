# CMake project for Modeler

# Contents
CMake script and Impressionist source code.  

# Changelog
20201015: release  

# Requirements

  - `Git`
    * (Windows) Install Git from `https://git-scm.com/downloads/` if not installed.
    * (Linux) Install from package manager (ex.`sudo apt-get install git`)
  - `CMake` version 2.6.3 or later.  
    * (Windows) Install CMake from `https://cmake.org/download/`
    * (Linux) Install from package manager (ex. `sudo apt-get install cmake`)
  - C/C++ compiler
    * (Windows) Install Visual Studio (`Visual Studio 2019 Community`, etc) 
    * (Linux) GCC is Usually installed by default
  - LAN connection to download source from official `FLTK` repo for first time.

# Basic usage

Execute following commands to build project (from directory of this README.md): 
  + `mkdir build`
    - Make build directory.
  + `cd build`
    - Move to build directory.
  + `cmake ..`
    - Generate native build script (for example, `GNU Make` script).
  + `cmake --build .`
    - Build with generated build script.
    - (Windows) You can also open generated `Impressionist.sln` with Visual Studio.

# To add your source file
  * Add header file (*.h) to folder `include`.
  * Add source file (*.cpp) to folder `src`.
  * Add source file position (src/*.cpp) to source list for `add_executable(...)` in `CMakeLists.txt`.
  * Run `cmake --build .` again.
