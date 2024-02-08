#pragma once

#include <flecs.h>
#include <string>

namespace eath
{
  struct ShaderName
  {
    std::string shaderPath;
  };
  struct ShaderProgram
  {
    flecs::entity vertex;
    flecs::entity fragment;
  };
  void register_shaders(flecs::world& ecs);
};

