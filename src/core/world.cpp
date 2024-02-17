#include "core/world.h"
#include "gfx/primitives.h"
#include "gfx/rendering.h"
#include "gfx/shaders.h"
#include "core/input.h"

static flecs::world* ecs = nullptr;

void eath::create_world()
{
  ecs = new flecs::world();
}

void eath::register_systems()
{
  register_input(*ecs);
  register_primitives(*ecs);
  register_shaders(*ecs);
  register_rendering(*ecs);
}

void eath::shutdown_world()
{
  delete ecs;
}

flecs::world& eath::get_world()
{
  return *ecs;
}

void eath::world_progress()
{
  if (ecs) // We can have engine without world at all, so we need to be defensive here
    ecs->progress();
}


