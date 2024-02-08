#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "platform/video.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/platform.h>

#include <vector>

// TODO: add resource manager for windows
static std::vector<SDL_Window*> g_windows;

eath::WindowHandle eath::init_window(int width, int height, int flags)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
    "Eath Engine: basic window sample",
    width,
    height,
    SDL_WINDOW_HIGH_PIXEL_DENSITY
  );
  if (!window)
  {
    printf("Cannot create a window\n");
    return false;
  }
  WindowHandle wh = g_windows.size();
  g_windows.emplace_back(window);

  // do a renderframe in bgfx and create a window by polling an event
  SDL_Event e;
  SDL_PollEvent( &e );
  bgfx::renderFrame();

  // initialize window handle
  bgfx::PlatformData pd{};

#if BX_PLATFORM_WINDOWS
  pd.nwh = SDL_GetProperty(SDL_GetWindowProperties(window), SDL_PROPERTY_WINDOW_WIN32_HWND_POINTER, NULL);
#elif BX_PLATFORM_OSX
  pd.nwh = SDL_GetProperty(SDL_GetWindowProperties(window), SDL_PROPERTY_WINDOW_COCOA_WINDOW_POINTER, NULL);
#elif BX_PLATFORM_LINUX
  pd.ndt = SDL_GetProperty(SDL_GetWindowProperties(window), SDL_PROPERTY_WINDOW_X11_DISPLAY_POINTER, NULL);
  pd.nwh = SDL_GetNumberProperty(SDL_GetWindowProperties(window), SDL_PROPERTY_WINDOW_X11_WINDOW_NUMBER, 0);
#elif BX_PLATFORM_EMSCRIPTEN
  pd.nwh = (void*)"#canvas";
#endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX ? BX_PLATFORM_LINUX ?

  int ww = width;
  int hh = height;
  SDL_GetWindowSizeInPixels(window, &ww, &hh);

  bgfx::Init bgfx_init;
  //bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
  bgfx_init.resolution.width = ww;
  bgfx_init.resolution.height = hh;
  bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
  bgfx_init.platformData = pd;
  if (!bgfx::init(bgfx_init))
  {
    printf("Cannot init BGFX\n");
    return false;
  }

  bgfx::setViewClear(
      0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x222222FF, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, ww, hh);

  return true;
}

void eath::destroy_window(eath::WindowHandle wh)
{
  if (wh >= g_windows.size() || g_windows[wh] == nullptr)
    return; // TODO: report error
  SDL_Window* window = g_windows[wh];
  SDL_DestroyWindow(window);
  g_windows[wh] = nullptr;
}

