cmake_minimum_required(VERSION 3.13)

project(eath-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EATH_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("src")

add_subdirectory("3rdParty")
add_subdirectory("samples")

