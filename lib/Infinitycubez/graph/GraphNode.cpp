#include "GraphNode.h"

#include "GraphEdge.h"
#include "Graph.h"

namespace infc
{

uint32_t GraphNode::countConnections() const
{
  return _graph->countConnectionsToNode(_id);
}

}


