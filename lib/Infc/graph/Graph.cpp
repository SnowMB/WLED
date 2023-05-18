#include "Graph.h"

#include "GraphNode.h"
#include "GraphEdge.h"

#include <algorithm>

namespace infc
{
  void Graph::setDefinition(GraphDefinition def)
  {
    _definition = std::move(def);
    _nodeCount = std::ranges::max(_definition, {}, [](Edge const &e)
                                  { return std::max(e.frontNode, e.backNode); }) +
                 1;
    _totalLeds = std::ranges::max(_definition, {}, &EdgeDefinition::onePastEndLed) + 1;
  }

  GraphEdge Graph::edge(uint32_t id) const
  {
    return {*this, id};
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
    std::ranges::count_if(_definition, [id](EdgeDefinition const &e)
                          { return e.frontNode == id && e.backNode == id; });
  }

  GraphEdge Graph::getNthEdgeOfNode(uint32_t node) const
  {
    return Graph::
  }

  GraphEdge Graph::getNthEdgeOfNodeButIgnoreEdge(uint32_t node, uint32_t edge)
  {
  }

}
