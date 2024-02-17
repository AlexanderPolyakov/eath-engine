#include <flecs.h>
#include <SDL3/SDL.h>
#include "core/input.h"
#include "core/flecs_helpers.h"

ECS_COMPONENT_DECLARE(mouse_motion);

void eath::register_input(flecs::world& ecs)
{
  ecs_component_named(ecs, mouse_motion, SDL_MouseMotionEvent);
}

