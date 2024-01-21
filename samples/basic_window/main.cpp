#include <stdio.h>
#include "core/update.h"
#include "core/shutdown.h"
#include "platform/video.h"


int main(int argc, const char** argv)
{
  const int width = 1500;
  const int height = 900;
  eath::WindowHandle wh = eath::init_window(width, height, 0);
  if (!eath::is_handle_valid(wh))
  {
    printf("Cannot init video\n");
    return 1;
  }

  while (eath::mainloop())
  {
  }
  eath::shutdown(wh);

  return 0;
}

