#pragma once

#include <bx/math.h> // replace with our vectors eventually
#include <math.h>

namespace eath
{
  struct Mat4x4
  {
    union
    {
      float m[16];
      float rc[4][4];
    };
  };

  struct Mat3x4
  {
    union
    {
      float m[12];
      float rc[3][4];
    };
  };

  Mat4x4 mtx_rotate_xyz(const bx::Vec3& rot);
  Mat4x4 mtx_translate(const bx::Vec3& translate);
  Mat4x4 mtx_ident();

#include "matrix.inl"
};


