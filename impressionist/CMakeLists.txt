cmake_minimum_required(VERSION 2.6.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Impressionist)

find_package(Git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_NEON=ON")

execute_process(
  COMMAND ${GIT_EXECUTABLE} clone https://github.com/fltk/fltk.git external/fltk 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
)

execute_process(
  COMMAND ${GIT_EXECUTABLE} checkout master
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk
)

set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/fltk)

# fltk_all: headers, libraries
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE external/fltk ${CMAKE_CURRENT_BINARY_DIR}/external/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

# fltk_hello
add_executable(fltk_hello fltk_hello.cpp)
target_link_libraries(fltk_hello PRIVATE fltk_all)

# Impressionist
add_executable(impressionist
  src/impressionist.cpp
  src/bitmap.cpp
  src/FltDesignUI.cpp
  src/impBrush.cpp
  src/impressionistDoc.cpp
  src/impressionistUI.cpp
  src/originalView.cpp
  src/paintView.cpp
  src/pointBrush.cpp
  src/triangleBrush.cpp
  src/circleBrush.cpp
  src/lineBrush.cpp
  src/scatteredPointBrush.cpp
  src/scatteredCircleBrush.cpp
)
target_include_directories(impressionist PRIVATE include/)
target_link_libraries(impressionist PRIVATE fltk_all)

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT impressionist)
