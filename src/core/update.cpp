#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include "core/update.h"
#include "core/world.h"

bool eath::mainloop()
{
  bool quit = false;

  //Event handler

  //While application is running
  //Handle events on queue
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) // poll for event
  {
    //User requests quit
    quit |= e.type == SDL_EVENT_QUIT;
  }

  world_progress();

  bgfx::frame();
  return !quit;
}

