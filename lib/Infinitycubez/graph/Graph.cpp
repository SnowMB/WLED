#include "Graph.h"

#include "GraphNode.h"
#include "GraphEdge.h"

#include <algorithm>

namespace infc
{
  constexpr bool compareFrontNode(EdgeDefinition const &a, EdgeDefinition const &b)
  {
    return a.frontNode < b.frontNode;
  }

  constexpr bool compareBackNode(EdgeDefinition const &a, EdgeDefinition const &b)
  {
    return a.frontNode < b.backNode;
  }

  constexpr bool compareEndLed(EdgeDefinition const &a, EdgeDefinition const &b)
  {
    return a.endLed < b.endLed;
  }

  void Graph::setDefinition(GraphDefinition def)
  {
    _definition = std::move(def);
    if (_definition.size() == 0)
    {
      _nodeCount = 0;
      _totalLeds = 0;
    }
    else
    {
      auto maxFrontNodeId = std::max_element(_definition.begin(), _definition.end(), compareFrontNode)->frontNode;
      auto maxBackNodeId = std::max_element(_definition.begin(), _definition.end(), compareBackNode)->backNode;
      _nodeCount = std::max(maxFrontNodeId, maxBackNodeId) + 1;
      _totalLeds = std::max_element(_definition.begin(), _definition.end(), compareEndLed)->endLed + 1;
    }
  }

  GraphEdge Graph::edge(uint32_t id) const
  {
    return {*this, _definition[id], id};
  }

  GraphEdge Graph::randomEdge() const
  {
    return edge(std::rand() % _definition.size());
  }

  GraphNode Graph::node(uint32_t id) const
  {
    return {*this, id};
  }

  GraphNode Graph::randomNode() const
  {
    return node(std::rand() % _nodeCount);
  }

  uint32_t Graph::countConnectionsToNode(uint32_t id) const
  {
    return std::count_if(_definition.begin(), _definition.end(), [id](EdgeDefinition const &e)
                         { return e.frontNode == id || e.backNode == id; });
  }

  GraphEdge Graph::getNthEdgeOfNode(uint32_t node, uint32_t n) const
  {
    for (uint32_t i = 0; i < _definition.size(); i++)
    {
      if (_definition[i].frontNode == node && n-- == 0)
      {
        return {*this, _definition[i], i, false};
      }
      if (_definition[i].backNode == node && n-- == 0)
      {
        return {*this, _definition[i], i, true};
      }
    }

    return {};
  }

  GraphEdge Graph::getNthEdgeOfNodeButIgnoreEdge(uint32_t node, uint32_t n, uint32_t edge) const
  {
    for (uint32_t i = 0; i < _definition.size(); i++)
    {
      if (i == edge) continue;

      if (_definition[i].frontNode == node && n-- == 0)
      {
        return {*this, _definition[i], i, false};
      }
      if (_definition[i].backNode == node && n-- == 0)
      {
        return {*this, _definition[i], i, true};
      }
    }

    return {};
  }
}
