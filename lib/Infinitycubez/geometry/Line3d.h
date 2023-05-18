#pragma once

#include "Vec3d.h"

struct Line3d
{
  Vec3d from, to;

  Vec3d direction() const
  {
    return to-from;
  }
};

inline Vec3d coordinateAlong(Line3d const& line, float factor)
{
  return line.from + line.direction() * factor;
}