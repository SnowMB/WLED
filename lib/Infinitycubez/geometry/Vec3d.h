#pragma once 

#include <cmath>

struct Vec3d;

struct Spher3d
{
  float r;
  float theta;
  float phi;

  explicit operator Vec3d();
};

struct Cyl3d
{
  float rho;
  float phi;
  float z;

  explicit operator Vec3d();

};

struct Vec3d
{
  float x;
  float y;
  float z;

  Vec3d() = default;
  inline Vec3d(float _x, float _y, float _z) : x{_x}, y{_y}, z{_z} {}

  explicit operator Cyl3d() { return {sqrtf(x*x+y*y), atan2f(x, y),z}; }
  explicit operator Spher3d() 
  { 
    float r = length();
    return {r, r==0.0f?0.0f:acosf(z/r), atan2f(x,y)};
  }

  inline Vec3d operator-() {return {-x, -y, -z};}

  inline float length() const {return sqrtf(x*x+y*y+z*z);}
  Vec3d normalize() const;
};

inline bool operator==(Vec3d const& a, Vec3d const& b)
{
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(Vec3d const& a, Vec3d const& b)
{
  return !(a==b);
}

inline Vec3d& operator+=(Vec3d& a, Vec3d const& b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

inline Vec3d& operator-=(Vec3d& a, Vec3d const& b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

inline Vec3d operator+(Vec3d const& a, Vec3d const& b)
{
  return 
  {
    a.x+b.x,
    a.y+b.y,
    a.z+b.z
  };
}

inline Vec3d operator-(Vec3d const& a, Vec3d const& b)
{
  return 
  {
    a.x-b.x,
    a.y-b.y,
    a.z-b.z
  };
}

inline float dot(Vec3d const& a, Vec3d const& b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline float operator*(Vec3d const& a, Vec3d const& b)
{
  return dot(a,b);
}

inline Vec3d operator*(Vec3d const& a, float b)
{
  return 
  {
    a.x*b,
    a.y*b,
    a.z*b
  };
}

inline Vec3d& operator*=(Vec3d& a, float b)
{
  a.x *= b;
  a.y *= b;
  a.z *= b;
  return a;
}

inline Vec3d operator*(float b, Vec3d const& a)
{
  return 
  {
    a.x*b,
    a.y*b,
    a.z*b
  };
}

inline Vec3d operator/(Vec3d const& a, float b)
{
  return 
  {
    a.x/b,
    a.y/b,
    a.z/b
  };
}

inline Vec3d& operator/=(Vec3d& a, float b)
{
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}

inline Vec3d cross(Vec3d const& a, Vec3d const& b)
{
  return 
  {
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x-b.z,
    a.x*b.y - a.y*b.x
  };
}

inline Vec3d rotateX(Vec3d const& v, float degree)
{
  auto cos_d = cosf(degree);
  auto sin_d = sinf(degree);

  return {v.x, v.y*cos_d-v.z*sin_d, v.y*sin_d+v.z*cos_d};
}






class NormVec3d : public Vec3d
{
public:
  NormVec3d() = default;
  inline NormVec3d(Vec3d const & vec) : Vec3d{vec.normalize()} {}
  inline NormVec3d(float x, float y, float z) : NormVec3d{Vec3d{x, y,  z}} {}

  constexpr float length() const {return 1.0f;}

  inline float x() {return Vec3d::x;}
  inline float y() {return Vec3d::y;}
  inline float z() {return Vec3d::z;}

  inline void set(float x, float y, float z) 
  {
    auto norm = Vec3d{x, y,  z}.normalize();
    Vec3d::x = norm.x;
    Vec3d::y = norm.y;
    Vec3d::z = norm.z;
  }

  inline void set(Vec3d const& vec)
  {
    auto norm = vec.normalize();
    Vec3d::x = norm.x;
    Vec3d::y = norm.y;
    Vec3d::z = norm.z;
  }

  NormVec3d operator-() {return NormVec3d{Vec3d::operator-()};}

private:
  using Vec3d::x;
  using Vec3d::y;
  using Vec3d::z;

/*  inline friend bool operator==(NormVec3d const& a, NormVec3d const& b)
  {
    return static_cast<Vec3d>(a) == static_cast<Vec3d>(b);
  }

  inline friend bool operator!=(NormVec3d const& a, NormVec3d const& b)
  {
    return !(a==b);
  }

  inline friend Vec3d operator+(NormVec3d const& a, NormVec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);

    return va+vb;
  }
  
  inline friend Vec3d operator+(NormVec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return va + b;
  }

  inline friend Vec3d operator+(Vec3d const& a, NormVec3d const& b)
  {
    Vec3d vb = static_cast<Vec3d>(b);
    return a + vb;
  }

  inline friend Vec3d operator-(NormVec3d const& a, NormVec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);

    return va-vb;
  }
  
  inline friend Vec3d operator-(NormVec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return va-b;
  }

  inline friend Vec3d operator-(Vec3d const& a, NormVec3d const& b)
  {
    Vec3d vb = static_cast<Vec3d>(b);
    return a-vb;
  }

  inline friend float dot(NormVec3d const& a, NormVec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);
    return dot(va, vb);
  }

  inline friend float dot(NormVec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return dot(va, b);
  }

  inline friend float dot(Vec3d const& a, NormVec3d const& b)
  {
    Vec3d vb = static_cast<Vec3d>(b);
    return dot(a, vb);
  }

  template<typename T>
  inline friend Vec3d operator*(NormVec3d const& a, T b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return va * b;
  }

  template<typename T>
  inline friend Vec3d operator*(T b, NormVec3d const& a)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return b * va
  }

  template<typename T>
  inline friend Vec3d operator/(NormVec3d const& a, T b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    return va / b;
  }

  inline friend Vec3d cross(Vec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);
    return cross (va, vb);
  }

  inline friend Vec3d cross(Vec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);
    return 
  }

  inline friend Vec3d cross(Vec3d const& a, Vec3d const& b)
  {
    Vec3d va = static_cast<Vec3d>(a);
    Vec3d vb = static_cast<Vec3d>(b);
    return 
    {
      va.y*vb.z - va.z*vb.y,
      va.z*vb.x - va.x-vb.z,
      va.x*vb.y - va.y*vb.x
    };
  }
*/
};

/*
inline float operator*(NormVec3d const& a, NormVec3d const& b)
{
  return dot(a,b);
}

inline float operator*(NormVec3d const& a, Vec3d const& b)
{
  return dot(a,b);
}

inline float operator*(Vec3d const& a, NormVec3d const& b)
{
  return dot(a,b);
}
*/

