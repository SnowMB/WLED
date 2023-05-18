#include "GraphEdge.h"

#include "Graph.h"
#include "GraphNode.h"

#include <cstdlib>

namespace infc
{
  GraphNode GraphEdge::front() const
  {
    return {*_graph, _reversed? _def->backNode : _def->frontNode};
  }

  GraphNode GraphEdge::back() const
  {
    return {*_graph, _reversed? _def->frontNode : _def->backNode};
  }

  GraphEdge GraphEdge::moveForwardRandom(bool avoidSameEdge) const
  {
    auto node = back();

    auto possibilities = node.countConnections();

    if (avoidSameEdge)
    {
      possibilities -= 1;
      if (_def->backNode == _def->frontNode) // loop
      {
        possibilities -=1;
      }
    }

    if (possibilities == 0)
    {
      return reverse();
    }

    auto rnd = std::rand() % possibilities;

    auto edge = avoidSameEdge? _graph->getNthEdgeOfNodeButIgnoreEdge(node.id(), rnd, _id) : _graph->getNthEdgeOfNode(node.id(), rnd);

    return edge;
  }
}