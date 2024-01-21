cmake_minimum_required(VERSION 3.13)

project(eath-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE INCLUDES inlude/*.h include/*.hpp)
file(GLOB_RECURSE SOURCES ./*.cpp ./*.c)

# TODO: move to individual libraries?
add_library(eath-engine STATIC ${INCLUDES} ${SOURCES})
target_include_directories(eath-engine PUBLIC include)
target_link_libraries(eath-engine PRIVATE bgfx SDL3::SDL3-static bimg flecs)

