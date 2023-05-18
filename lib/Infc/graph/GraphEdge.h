#pragma once

#include <cstdint>

namespace infc
{
class Graph;
class GraphNode;

class GraphEdge
{
public:
  inline GraphEdge() = default;
  inline GraphEdge(Graph const &g, int id, bool reverse = false) : _graph{&g}, _id{id}, _reverse{reverse} {}

  inline int id() { return _id; }

  GraphEdge reverse() const;

  GraphNode front() const;
  GraphNode back() const;

  GraphEdge moveForwardRandom() const;

  inline operator bool() const {
    return _graph && _id >= 0; 
  }

private:
  Graph const *_graph = nullptr;
  int _id = -1;
  bool _reverse = false;
};

}