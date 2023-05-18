#include "Vec3d.h"


Spher3d::operator Vec3d()
{ 
  return {r * sinf(theta) * cosf(phi), r * sinf(theta) * sinf(phi), r * cosf(theta)};
}

Cyl3d::operator Vec3d() 
{ 
  return {rho * cosf(phi), rho * sinf(phi), z}; 
};

Vec3d Vec3d::normalize() const 
{
  return (*this)/length();
}