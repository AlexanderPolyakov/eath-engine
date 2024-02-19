# Eath Engine
## Introduction
Eath Engine is a game engine aimed to provide an easy way to build games. Particularly in Dungeon Crawler genre with provided tools and project samples.

## Current status
It's in the active and early development stage, so many things will change, but underlying principle
is that it's an engine powered by ECS, so things are data driven.

One thing to note at this stage is that integration with flecs is done via C api, as it allows
named components, which is one of the main requirements, as it allow to reuse types and more readily
integrate scripting languages. So instead of bloating your game with tens and hundreds of types we
aim to provide you with a simple and elegant system which is based on simple types, like floats, vectors,
matrices, arrays and tables.

No integration of scripting language is done yet and several candidates are: Luau or daScript.

## Goal
Goal is to provide an engine loader executable which can be used to entirely encompass your game as
all functionality of the game should be specified in data and scripts/systems. While user should
still be able to compile their own shaders and systems, but all the heavy loading of glueing it all
together should be done by the engine.

## Platforms
In principle it should work on any platform `bgfx` and `SDL` works, but currently only macOS is being
actively developed on with Windows and Emscripten versions following soon (target of middle of March 2024).

## Dependencies
Eath Engine is built upon a set of open source libraries:
* `bgfx` - rendering
* `SDL` - windowing and input
* `flecs` - ECS framework
