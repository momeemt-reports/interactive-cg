cmake_minimum_required(VERSION 2.6.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Modeler)

find_package(Git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_NEON=ON")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

execute_process(
  COMMAND ${GIT_EXECUTABLE} clone https://github.com/fltk/fltk.git external/fltk 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
)

execute_process(
  COMMAND ${GIT_EXECUTABLE} checkout release-1.3.5
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk
)

# GL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/fltk)

# fltk_all: headers, libraries
add_library(fltk_all INTERFACE)
target_include_directories(fltk_all INTERFACE external/fltk ${CMAKE_CURRENT_BINARY_DIR}/external/fltk)
target_link_libraries(fltk_all INTERFACE fltk fltk_gl fltk_images)

# Modeler
add_executable(modeler
  src/animatoruiwindows.cxx
  src/camera.cpp
  src/curve.cpp
  src/curveevaluator.cpp
  src/graphwidget.cpp
  src/imageio.cpp
  src/indicatorwindow.cpp
  src/linearcurveevaluator.cpp
  src/main.cpp
  src/modelerapp.cpp
  src/modelerdraw.cpp
  src/modelerui.cpp
  src/modelerview.cpp
  src/particleSystem.cpp
  src/point.cpp
  src/rect.cpp
  src/rulerwindow.cpp
)

target_include_directories(modeler PRIVATE include/)
target_link_libraries(modeler PRIVATE fltk_all)
target_link_libraries(modeler PRIVATE OpenGL::GLU)


# Robotarm
add_executable(robotarm
  src/animatoruiwindows.cxx
  src/camera.cpp
  src/curve.cpp
  src/curveevaluator.cpp
  src/graphwidget.cpp
  src/imageio.cpp
  src/indicatorwindow.cpp
  src/linearcurveevaluator.cpp
  src/modelerapp.cpp
  src/modelerdraw.cpp
  src/modelerui.cpp
  src/modelerview.cpp
  src/particleSystem.cpp
  src/point.cpp
  src/rect.cpp
  src/robotarm.cpp
  src/rulerwindow.cpp
)
target_include_directories(robotarm PRIVATE include/)
target_link_libraries(robotarm PRIVATE fltk_all)
target_link_libraries(robotarm PRIVATE OpenGL::GLU)

# Set as default project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT modeler)
