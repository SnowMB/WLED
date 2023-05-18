#pragma once

#include "Plane3d.h"

#include <algorithm>

struct Box3d
{
  Vec3d A, B;

  float width() const {return std::abs(A.x-B.x);}
  float depth() const {return std::abs(A.y-B.y);}
  float height() const {return std::abs(A.z-B.z);}

  float minX() const {return std::min(A.x, B.x);}
  float maxX() const {return std::max(A.x, B.x);}

  float minY() const {return std::min(A.y, B.y);}
  float maxY() const {return std::max(A.y, B.y);}

  float minZ() const {return std::min(A.z, B.z);}
  float maxZ() const {return std::max(A.z, B.z);}

  Vec3d CornerMax() const {return {maxX(), maxY(), maxZ()};}
  Vec3d CornerMin() const {return {minX(), minY(), minZ()};}

  Plane3d right() const {return {CornerMax(), {1,0,0}};}
  Plane3d left() const {return {CornerMin(), {-1,0,0}};}

  Plane3d back() const {return {CornerMax(), {0,1,0}};}
  Plane3d front() const {return {CornerMin(), {0,-1,0}};}

  Plane3d top() const {return {CornerMax(), {0,0,1}};}
  Plane3d bottom() const {return {CornerMin(), {0,0,-1}};}

  bool intersectsWith(Box3d const& b)
  {
    return ( minX() <= b.maxX() && maxX() >= b.minX()) &&
         (minY() <= b.maxY() && maxY() >= b.minY()) &&
         (minZ() <= b.maxZ() && maxZ() >= b.minZ());
  }

  bool intersectsWith(Line3d const& l)
  {
    if (contains(l.from) || contains(l.to))
    {
      return true;
    }
  }

  bool contains(Vec3d const& c)
  {
    return minX() <= c.x && maxX() >= c.x &&
           minY() <= c.y && maxY() >= c.y &&
           minZ() <= c.z && maxZ() >= c.z;
  }

  void translate(Vec3d const& v)
  {
    A = A+v;
    B = B+v;
  }
};


inline Box3d calculateBoundingBox(Vec3d const* begin, Vec3d const* end)
{
  Vec3d a = *begin;
  Vec3d b = *begin;

  for (++begin; begin != end; begin++)
  {
    a.x = std::min(begin->x, a.x);
    a.y = std::min(begin->y, a.y);
    a.z = std::min(begin->z, a.z);

    b.x = std::max(begin->x, b.x);
    b.y = std::max(begin->y, b.y);
    b.z = std::max(begin->z, b.z);
  }
  return {a,b};
}

inline Box3d calculateBoundingBox(Line3d const& l)
{
  return {l.from, l.to};
}