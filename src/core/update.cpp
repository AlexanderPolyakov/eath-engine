#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include "core/update.h"
#include "core/world.h"
#include "core/input.h"

#include "core/flecs_helpers.h"


bool eath::mainloop()
{
  bool quit = false;

  pre_raw_input();

  //While application is running
  //Handle events on queue
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) // poll for event
  {
    if (process_raw_input(e)) // that was input, and we've processed it
      continue;
    switch (e.type)
    {
      case SDL_EVENT_QUIT:
        quit = true;
        break;
    };
  }

  world_progress();

  bgfx::frame();
  return !quit;
}

