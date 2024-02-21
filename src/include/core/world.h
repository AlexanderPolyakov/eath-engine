#pragma once

#include "flecs.h"

namespace eath
{
  void create_world();
  void register_systems();
  void shutdown_world();

  void world_progress();

  ecs_world_t* get_world();
};

