#pragma once

#include "Vec3d.h"
#include "Line3d.h"

#include <cmath>

struct Plane3d
{
  Vec3d x0;
  NormVec3d n;
};

inline float distanceFromPointToPlane(Vec3d const& point, Plane3d const& plane)
{
  auto w = point - plane.x0;
  return plane.n*w;
}

inline bool isPointInsidePlane(Vec3d const& point, Plane3d const& plane, float epsilon=1e-6f)
{
  return std::abs(distanceFromPointToPlane(point, plane))<epsilon;
}

inline bool isLineInsidePlane(Line3d const& l, Plane3d const& p, float epsilon=1e-6f)
{
  return isPointInsidePlane(l.from, p, epsilon) && isPointInsidePlane(l.to, p, epsilon);
}

struct IntersectionResult
{
  Line3d line;

  float distP1;
  float distP2;

  bool isIntersected() const {return (distP1 * distP2) <= 0;}
  float factor() const {return std::abs(distP1/(distP1-distP2));}
  Vec3d point() const {return line.from + line.direction()*factor();}

  operator bool() const {return isIntersected();}
};

inline IntersectionResult isPlaneIntersectedBy(Plane3d const& p, Line3d const& l)
{
  auto da = distanceFromPointToPlane(l.from, p);
  auto db = distanceFromPointToPlane(l.to, p);

  return {l, da, db};
}