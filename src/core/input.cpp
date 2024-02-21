#include <flecs.h>
#include <SDL3/SDL.h>
#include "core/input.h"
#include "core/world.h"
#include "core/flecs_helpers.h"

ECS_COMPONENT_DECLARE(mouse_motion);
ECS_COMPONENT_DECLARE(keyboard_state);

void eath::register_input(ecs_world_t* ecs)
{
  ecs_component_named(ecs, mouse_motion, SDL_MouseMotionEvent);
  ecs_component_named(ecs, keyboard_state, KeyboardState);

  KeyboardState ks;
  memset(&ks, 0, sizeof(KeyboardState));
  ecs_cset_named_singleton(ecs, keyboard_state, ks);
}

void eath::pre_raw_input()
{
  ecs_world_t* ecs = get_world();

  SDL_MouseMotionEvent zeroMotion = {0};
  ecs_cset_named_singleton(ecs, mouse_motion, zeroMotion);

  KeyboardState* ks = ecs_get_mut_named_singleton(ecs, keyboard_state, KeyboardState);
  ks->pressed.reset();
}

static void on_key(ecs_world_t* ecs, const SDL_Event& e)
{
  const bool isDown = e.type == SDL_EVENT_KEY_DOWN;
  const SDL_KeyboardEvent& ke = e.key;

  eath::KeyboardState* ks = ecs_get_mut_named_singleton(ecs, keyboard_state, eath::KeyboardState);
  SDL_Scancode scancode = ke.keysym.scancode;
  const bool newState = isDown;
  const bool oldState = ks->curState[scancode];
  if (newState && !oldState)
    ks->pressed[scancode] = true;
  if (!newState && oldState)
    ks->released[scancode] = true;
  ks->curState[scancode] = newState;
}

bool eath::process_raw_input(const SDL_Event& e)
{
  ecs_world_t* ecs = get_world();
  switch (e.type)
  {
    case SDL_EVENT_MOUSE_MOTION:
      ecs_cset_named_singleton(ecs, mouse_motion, e.motion);
      return true;
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
      on_key(ecs, e);
      return true;
  };

  // Not an input
  return false;
}

