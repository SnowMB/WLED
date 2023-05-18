#pragma once

#include <cstdint>
#include <vector>

namespace infc
{
struct EdgeDefinition
{
  uint32_t id;
  uint32_t startLed;
  uint32_t onePastEndLed;
  uint32_t frontNode;
  uint32_t backNode;
};

using GraphDefinition = std::vector<EdgeDefinition>;
}