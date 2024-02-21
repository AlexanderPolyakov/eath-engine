#include "core/world.h"
#include "gfx/primitives.h"
#include "gfx/rendering.h"
#include "gfx/shaders.h"
#include "gfx/buffer.h"
#include "gfx/view.h"
#include "core/input.h"

static ecs_world_t* ecs = nullptr;

void eath::create_world()
{
  ecs = ecs_init();
}

void eath::register_systems()
{
  register_buffers(ecs);
  register_input(ecs);
  register_primitives(ecs);
  register_shaders(ecs);
  register_view(ecs);
  register_rendering(ecs);
}

void eath::shutdown_world()
{
  ecs_fini(ecs);
}

ecs_world_t* eath::get_world()
{
  return ecs;
}

void eath::world_progress()
{
  if (ecs) // We can have engine without world at all, so we need to be defensive here
    ecs_progress(ecs, 0);
}


