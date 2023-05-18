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

    inline uint32_t edgeCount() {return _definition.size();}
    inline uint32_t nodeCount() {return _nodeCount;}
    inline uint32_t totalLeds(){ return _totalLeds;}

    void setDefinition(GraphDefinition def);

    GraphEdge edge(uint32_t id) const;
    GraphEdge randomEdge() const;

    GraphNode node(uint32_t id) const;
    GraphNode randomNode() const;

    GraphNode frontNodeForEdge(uint32_t id) const;
    GraphNode backNodeForEdge(uint32_t id) const;

    uint32_t countConnectionsToNode(uint32_t id) const;

    GraphEdge getNthEdgeOfNode(uint32_t node) const;
    GraphEdge getNthEdgeOfNodeButIgnoreEdge(uint32_t node, uint32_t edge);

  private:
    uint32_t _totalLeds = 0;
    uint32_t _nodeCount = 0;

    GraphDefinition _definition;
  };

 
}
