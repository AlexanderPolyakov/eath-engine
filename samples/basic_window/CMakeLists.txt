cmake_minimum_required(VERSION 3.13)

project(basic_window)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(
  GLOB
  SOURCES
  ./*.cpp
  ./*.c
  ./*.h)

add_executable(basic_window ${SOURCES})
target_link_libraries(basic_window PRIVATE bgfx SDL3::SDL3-static bimg flecs eath-engine)
