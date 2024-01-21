cmake_minimum_required(VERSION 3.13)

project(3rdparty)

set(BGFX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bgfx" CACHE STRING "Location of bgfx.")
set(BIMG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bimg" CACHE STRING "Location of bimg.")
set(BX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bx" CACHE STRING "Location of bx.")
set(SDL_STATIC ON)

add_subdirectory("bgfx.cmake")
add_subdirectory("flecs")
add_subdirectory(SDL EXCLUDE_FROM_ALL)

