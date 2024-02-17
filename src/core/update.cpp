#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include "core/update.h"
#include "core/world.h"
#include "core/input.h"

#include "core/flecs_helpers.h"


bool eath::mainloop()
{
  bool quit = false;

  //Event handler
  flecs::world& ecs = get_world();
  flecs::entity source = ecs.entity();

  //While application is running
  //Handle events on queue
  SDL_Event e;
  SDL_MouseMotionEvent zeroMotion = {0};
  ecs_cset_named_singleton(ecs.c_ptr(), mouse_motion, zeroMotion);
  while (SDL_PollEvent(&e) != 0) // poll for event
  {
    switch (e.type)
    {
      case SDL_EVENT_QUIT:
        quit = true;
        break;
      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        break;
      case SDL_EVENT_MOUSE_MOTION:
        {
          ecs_cset_named_singleton(ecs.c_ptr(), mouse_motion, e.motion);
        }
        break;
    };
  }

  world_progress();

  bgfx::frame();
  return !quit;
}

