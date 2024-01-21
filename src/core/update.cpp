#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include "core/update.h"

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

  bgfx::frame();
  return !quit;
}

