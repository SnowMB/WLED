#include "GraphEdge.h"

#include "Graph.h"
#include "GraphNode.h"

namespace infc
{
  GraphEdge GraphEdge::reverse() const
  {
    return {*_graph, _id, !_reverse};
  }

  GraphNode GraphEdge::front()
  {
    return _reverse? _graph->backNodeForEdge(_id) : _graph->frontNodeForEdge(id);
  }

  GraphNode GraphEdge::back()
  {
    return _reverse? _graph->frontNodeForEdge(_id) : _graph->backNodeForEdge(id);
  }

  GraphEdge GraphEdge::moveForwardRandom() const
  {
    auto node = back();

    auto possibilities = node.countConnections() - (front.id() == node.id() ? 2 : 1); // at least one connection is self

    if (possibilities == 0)
    {
      return reverse();
    }
    else
    {
      auto it = node.begin();
      auto rnd = random(0, possibilities);

      while ((*it).id() == _id)
      {
        it++;
      }

      while (rnd > 0)
      {
        it++;
        while ((*it).id() == _id)
        {
          it++;
        }
        rnd--;
      }

      return *it;
    }
  }

private:
  Graph const *_graph;
  uint32_t _id;
  bool _reverse;
};

}