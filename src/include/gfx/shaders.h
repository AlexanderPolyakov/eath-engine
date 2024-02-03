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
    flecs::entity_t vertex;
    flecs::entity_t fragment;
  };
  void register_shaders(flecs::world& ecs);
};

