
inline Mat4x4 mtx_rotate_xyz(const bx::Vec3& rot)
{
  Mat4x4 out;

  // Just aliases to follow convention from here: https://en.wikipedia.org/wiki/Rotation_matrix
  const float& alpha = rot.x;
  const float& beta  = rot.y;
  const float& gamma = rot.z;
  out.rc[0][0] = cosf(beta) * cosf(gamma);
  out.rc[0][1] = sinf(alpha) * sinf(beta) * cosf(gamma) - cosf(alpha) * sinf(gamma);
  out.rc[0][2] = cosf(alpha) * sinf(beta) * cosf(gamma) + sinf(alpha) * sinf(gamma);
  out.rc[0][3] = 0;

  out.rc[1][0] = cosf(beta) * sinf(gamma);
  out.rc[1][1] = sinf(alpha) * sinf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma);
  out.rc[1][2] = cosf(alpha) * sinf(beta) * sinf(gamma) - sinf(alpha) * cosf(gamma);
  out.rc[1][3] = 0;

  out.rc[2][0] = -sinf(beta);
  out.rc[2][1] = sinf(alpha) * cosf(beta);
  out.rc[2][2] = cosf(alpha) * cosf(beta);
  out.rc[2][3] = 0;

  out.rc[3][0] = 0;
  out.rc[3][1] = 0;
  out.rc[3][2] = 0;
  out.rc[3][3] = 1;

  return out;
}

inline Mat4x4 mtx_ident()
{
  Mat4x4 out;

  memset(out.m, 0, sizeof(float) * 16);
  // ident
  out.rc[0][0] = 1;
  out.rc[1][1] = 1;
  out.rc[2][2] = 1;
  out.rc[3][3] = 1;
  return out;
}

inline Mat4x4 mtx_translate(const bx::Vec3& transl)
{
  Mat4x4 out = mtx_ident();

  out.rc[3][0] = transl.x;
  out.rc[3][1] = transl.y;
  out.rc[3][2] = transl.z;

  return out;
}

