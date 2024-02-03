#pragma once
#include <bx/math.h>

namespace eath
{
inline bx::Vec3 operator+(const bx::Vec3& lhs, const bx::Vec3& rhs)
{
  return bx::add(lhs, rhs);
}

inline bx::Vec3 operator-(const bx::Vec3& lhs, const bx::Vec3& rhs)
{
  return bx::sub(lhs, rhs);
}
};

