#pragma once
#include <bx/math.h>

namespace eath
{
  struct CameraPosition
  {
    bx::Vec3 pos;
  };

  struct CameraYPR
  {
    bx::Vec3 ypr;
  };

  struct CameraMatrix
  {
    float m[16];
  };

  struct ViewMatrix
  {
    float m[16];
  };

  struct ProjMatrix
  {
    float m[16];
  };
};
