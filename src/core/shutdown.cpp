#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include "core/shutdown.h"
#include "platform/video.h"

void eath::shutdown(ResHandle wh)
{
  bgfx::shutdown();

  destroy_window(wh);
  SDL_Quit();
}

