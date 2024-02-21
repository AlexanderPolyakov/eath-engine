#pragma once

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_events.h>
#include <bitset>

extern ECS_COMPONENT_DECLARE(mouse_motion);
extern ECS_COMPONENT_DECLARE(keyboard_state);

namespace eath
{
  struct KeyboardState
  {
    std::bitset<SDL_NUM_SCANCODES> curState;
    std::bitset<SDL_NUM_SCANCODES> pressed;
    std::bitset<SDL_NUM_SCANCODES> released;
  };
  void register_input(ecs_world_t* ecs);

  void pre_raw_input();
  bool process_raw_input(const SDL_Event& e);
};
