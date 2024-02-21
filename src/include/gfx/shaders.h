#pragma once

#include <flecs.h>
#include <string>

extern ECS_COMPONENT_DECLARE(shaders__path);
extern ECS_COMPONENT_DECLARE(shaders__vertex_shader);
extern ECS_COMPONENT_DECLARE(shaders__fragment_shader);
extern ECS_COMPONENT_DECLARE(shaders__handle);
extern ECS_COMPONENT_DECLARE(shaders__program_handle);

namespace eath
{
  struct ShaderProgram
  {
    flecs::entity vertex;
    flecs::entity fragment;
  };
  void register_shaders(ecs_world_t* ecs);
};

