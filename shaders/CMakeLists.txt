cmake_minimum_required(VERSION 3.13)

project(shaders)

set(SHADERC ${EATH_ROOT_DIR}/build/3rdParty/bgfx.cmake/cmake/bgfx/shaderc)

file(
  GLOB
  VS_SOURCES
  ./*_vs.sc)

file(
  GLOB
  FS_SOURCES
  ./*_fs.sc)

