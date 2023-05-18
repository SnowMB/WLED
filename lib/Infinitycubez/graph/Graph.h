#pragma once

#include "GraphDefinition.h"

namespace infc
{
  class GraphEdge;
  class GraphNode;

  class Graph
  {
  public:
    virtual ~Graph() = default;

    inline uint32_t edgeCount() {return static_cast<uint32_t>(_definition.size());}
    inline uint32_t nodeCount() {return _nodeCount;}
    inline int totalLeds(){ return _totalLeds;}

    void setDefinition(GraphDefinition def);

    GraphEdge edge(uint32_t id) const;
    GraphEdge randomEdge() const;

    GraphNode node(uint32_t id) const;
    GraphNode randomNode() const;

    uint32_t countConnectionsToNode(uint32_t id) const;

    GraphEdge getNthEdgeOfNode(uint32_t node, uint32_t n) const;
    GraphEdge getNthEdgeOfNodeButIgnoreEdge(uint32_t node, uint32_t n, uint32_t edge) const;

  private:
    int _totalLeds = 0;
    uint32_t _nodeCount = 0;

    GraphDefinition _definition;
  };

 
}
