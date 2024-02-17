#!/bin/bash
mkdir shaders/metal
./build/3rdParty/bgfx.cmake/cmake/bgfx/shaderc -f shaders/simple_vs.sc -o shaders/metal/simple_vs.bin --type vertex --platform osx -p metal -i 3rdParty/bgfx/src --varyingdef 3rdParty/bgfx/src/varying.def.sc
./build/3rdParty/bgfx.cmake/cmake/bgfx/shaderc -f shaders/simple_fs.sc -o shaders/metal/simple_fs.bin --type fragment --platform osx -p metal -i 3rdParty/bgfx/src --varyingdef 3rdParty/bgfx/src/varying.def.sc
