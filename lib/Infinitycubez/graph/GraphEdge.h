#pragma once

#include <cstdint>
#include <cmath>

#include "GraphDefinition.h"

namespace infc
{
  class Graph;
  class GraphNode;

  class GraphEdge
  {
  public:
    GraphEdge() = default;

    GraphEdge(Graph const &graph, EdgeDefinition const &def, uint32_t id, bool reversed = false)
        : _graph{&graph},
          _def{&def},
          _id{id},
          _reversed{reversed}
    {
    }

    inline int id() { return _id; }

    inline bool isReversed() const
    {
      return _reversed;
    }

    inline int size() const
    {
      return countLeds(*_def);
    }

    inline GraphEdge reverse() const
    {
      return {*_graph, *_def, _id, !_reversed};
    }

    inline GraphEdge operator-() const
    {
      return reverse();
    }

    inline int ledAt(int index)
    {
      return _reversed ? (_def->endLed - index) : (_def->startLed + index);
    }

    GraphNode front() const;
    GraphNode back() const;

    GraphEdge moveForwardRandom(bool avoidSameEdge = true) const;

    inline operator bool() const
    {
      return _graph != nullptr;
    }

  private:
    Graph const *_graph = nullptr;
    EdgeDefinition const *_def;
    uint32_t _id = 0;
    bool _reversed;
  };
}