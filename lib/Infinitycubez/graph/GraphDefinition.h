#pragma once

#include <cstdint>
#include <vector>

namespace infc
{
struct EdgeDefinition
{
  uint32_t startLed;
  uint32_t endLed;
  uint32_t frontNode;
  uint32_t backNode;
};

inline int countLeds(EdgeDefinition const& d) 
{
  return d.endLed - d.startLed;
}

using GraphDefinition = std::vector<EdgeDefinition>;
}