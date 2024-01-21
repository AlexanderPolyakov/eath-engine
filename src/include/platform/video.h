#pragma once

#include "core/handles.h"

namespace eath
{
  using WindowHandle = ResHandle;

  WindowHandle init_window(int width, int height, int flags);
  void destroy_window(WindowHandle wh);
};

