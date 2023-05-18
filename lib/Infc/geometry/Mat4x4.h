#pragma once
#include "Vec3d.h"
#include <array>
#include <algorithm>
#include <Debug.h>

#include <cmath>

class Mat4x4
{
public:
  Mat4x4() = default;
  Mat4x4(Mat4x4 const& other) = default;
  Mat4x4(Mat4x4 && other) = default;
  Mat4x4& operator=(Mat4x4 const& other) = default;
  Mat4x4& operator=(Mat4x4 && other) = default;

  Mat4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44):
    m{m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44}
  {

  }

  inline float m11 () const {return m[0][0];}
  inline float m12 () const {return m[0][1];}
  inline float m13 () const {return m[0][2];}
  inline float m14 () const {return m[0][3];}

  inline float m21 () const {return m[1][0];}
  inline float m22 () const {return m[1][1];}
  inline float m23 () const {return m[1][2];}
  inline float m24 () const {return m[1][3];}

  inline float m31 () const {return m[2][0];}
  inline float m32 () const {return m[2][1];}
  inline float m33 () const {return m[2][2];}
  inline float m34 () const {return m[2][3];}

  inline float m41 () const {return m[3][0];}
  inline float m42 () const {return m[3][1];}
  inline float m43 () const {return m[3][2];}
  inline float m44 () const {return m[3][3];}




  //                              gamma    beta   alpha
  static inline Mat4x4 forRPY(float r, float p, float y)
  {
    auto sr = sinf(r);
    auto cr = cosf(r);
    auto sp = sinf(p);
    auto cp = cosf(p);
    auto sy = sinf(y);
    auto cy = cosf(y);

    //Debug::println("r: ", r, " p: ", p , " y: ", y);
    //Debug::println("sinf(r): ", sr);
    //Debug::println("cosf(r): ", cr);
    //Debug::println("sinf(p): ", sp);
    //Debug::println("cosf(p): ", cp);
    //Debug::println("sinf(y): ", sy);
    //Debug::println("cosf(y): ", cy);

    return {
      cp*cy, sr*sp*cy-cr*sy, cr*sp*cy+sr*sy, 0,
      cp*sy, sr*sp*sy+cr*cy, cr*sp*sy-sr*cy, 0,
      -sp  , sr*cp         , cr*cp         , 0,
      0    , 0             , 0             , 1
    };
  }  

  //                              gamma    beta   alpha
  static inline Mat4x4 forRPYrev(float r, float p, float y)
  {
    auto sr = sinf(r);
    auto cr = cosf(r);
    auto sp = sinf(p);
    auto cp = cosf(p);
    auto sy = sinf(y);
    auto cy = cosf(y);

    //Debug::println("r: ", r, " p: ", p , " y: ", y);
    //Debug::println("sinf(r): ", sr);
    //Debug::println("cosf(r): ", cr);
    //Debug::println("sinf(p): ", sp);
    //Debug::println("cosf(p): ", cp);
    //Debug::println("sinf(y): ", sy);
    //Debug::println("cosf(y): ", cy);
    return {
      cp*cy,         -cp*sy,          sp,    0,
      sp*sr*cy+cr*sy, cr*cy-sp*sr*sy,-cp*sr, 0,
      sr*sy-sp*cr*cy, sp*cr*sy+sr*cy, cp*cr, 0,
      0,              0             , 0    , 1
    };
  }  

  inline friend bool operator==(Mat4x4 const& a, Mat4x4 const& b)
  {
    return a.m == b.m;
  }

  inline friend bool operator!=(Mat4x4 const& a, Mat4x4 const& b)
  {
    return !(a == b);
  }


  inline friend Vec3d operator*(const Mat4x4& matrix, const Vec3d& vector)
  {
      float x, y, z, w;
      x = vector.x * matrix.m[0][0] +
          vector.y * matrix.m[1][0] +
          vector.z * matrix.m[2][0] +
          matrix.m[3][0];
      y = vector.x * matrix.m[0][1] +
          vector.y * matrix.m[1][1] +
          vector.z * matrix.m[2][1] +
          matrix.m[3][1];
      z = vector.x * matrix.m[0][2] +
          vector.y * matrix.m[1][2] +
          vector.z * matrix.m[2][2] +
          matrix.m[3][2];
      w = vector.x * matrix.m[0][3] +
          vector.y * matrix.m[1][3] +
          vector.z * matrix.m[2][3] +
          matrix.m[3][3];
      if (w == 1.0f)
          return Vec3d{x, y, z};
      else
          return Vec3d{x / w, y / w, z / w};
  }

  inline friend Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2)
  { 
    Mat4x4 m;
    m.m[0][0] = m1.m[0][0] * m2.m[0][0]
              + m1.m[1][0] * m2.m[0][1]
              + m1.m[2][0] * m2.m[0][2]
              + m1.m[3][0] * m2.m[0][3];
    m.m[0][1] = m1.m[0][1] * m2.m[0][0]
              + m1.m[1][1] * m2.m[0][1]
              + m1.m[2][1] * m2.m[0][2]
              + m1.m[3][1] * m2.m[0][3];
    m.m[0][2] = m1.m[0][2] * m2.m[0][0]
              + m1.m[1][2] * m2.m[0][1]
              + m1.m[2][2] * m2.m[0][2]
              + m1.m[3][2] * m2.m[0][3];
    m.m[0][3] = m1.m[0][3] * m2.m[0][0]
              + m1.m[1][3] * m2.m[0][1]
              + m1.m[2][3] * m2.m[0][2]
              + m1.m[3][3] * m2.m[0][3];

    m.m[1][0] = m1.m[0][0] * m2.m[1][0]
              + m1.m[1][0] * m2.m[1][1]
              + m1.m[2][0] * m2.m[1][2]
              + m1.m[3][0] * m2.m[1][3];
    m.m[1][1] = m1.m[0][1] * m2.m[1][0]
              + m1.m[1][1] * m2.m[1][1]
              + m1.m[2][1] * m2.m[1][2]
              + m1.m[3][1] * m2.m[1][3];
    m.m[1][2] = m1.m[0][2] * m2.m[1][0]
              + m1.m[1][2] * m2.m[1][1]
              + m1.m[2][2] * m2.m[1][2]
              + m1.m[3][2] * m2.m[1][3];
    m.m[1][3] = m1.m[0][3] * m2.m[1][0]
              + m1.m[1][3] * m2.m[1][1]
              + m1.m[2][3] * m2.m[1][2]
              + m1.m[3][3] * m2.m[1][3];

    m.m[2][0] = m1.m[0][0] * m2.m[2][0]
              + m1.m[1][0] * m2.m[2][1]
              + m1.m[2][0] * m2.m[2][2]
              + m1.m[3][0] * m2.m[2][3];
    m.m[2][1] = m1.m[0][1] * m2.m[2][0]
              + m1.m[1][1] * m2.m[2][1]
              + m1.m[2][1] * m2.m[2][2]
              + m1.m[3][1] * m2.m[2][3];
    m.m[2][2] = m1.m[0][2] * m2.m[2][0]
              + m1.m[1][2] * m2.m[2][1]
              + m1.m[2][2] * m2.m[2][2]
              + m1.m[3][2] * m2.m[2][3];
    m.m[2][3] = m1.m[0][3] * m2.m[2][0]
              + m1.m[1][3] * m2.m[2][1]
              + m1.m[2][3] * m2.m[2][2]
              + m1.m[3][3] * m2.m[2][3];

    m.m[3][0] = m1.m[0][0] * m2.m[3][0]
              + m1.m[1][0] * m2.m[3][1]
              + m1.m[2][0] * m2.m[3][2]
              + m1.m[3][0] * m2.m[3][3];
    m.m[3][1] = m1.m[0][1] * m2.m[3][0]
              + m1.m[1][1] * m2.m[3][1]
              + m1.m[2][1] * m2.m[3][2]
              + m1.m[3][1] * m2.m[3][3];
    m.m[3][2] = m1.m[0][2] * m2.m[3][0]
              + m1.m[1][2] * m2.m[3][1]
              + m1.m[2][2] * m2.m[3][2]
              + m1.m[3][2] * m2.m[3][3];
    m.m[3][3] = m1.m[0][3] * m2.m[3][0]
              + m1.m[1][3] * m2.m[3][1]
              + m1.m[2][3] * m2.m[3][2]
              + m1.m[3][3] * m2.m[3][3];
    return m;
  }

private:
  std::array<std::array<float, 4>, 4> m = 
  {{
    {{1,0,0,0}},
    {{0,1,0,0}},
    {{0,0,1,0}},
    {{0,0,0,1}}
  }};
};


