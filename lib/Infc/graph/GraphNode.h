#pragma once

#include <cstdint>

namespace infc
{

class Graph;
class GraphNode;

class GraphNode
{
public:
  inline GraphEdge() = default;
  inline GraphNode(Graph const&g, int id) : _graph{&g}, _id{id} {}

  inline int id() const { return _id; }

  uint32_t countConnections() const;

  inline operator bool() const {
    return _graph && _id >= 0; 
  }

private:
  Graph const* _graph = nullptr;
  int _id = -1;
};

}
