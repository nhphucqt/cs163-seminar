#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct GraphEdge {
    int u, v, w;
};

struct GraphSuccessor {
    int v, w;
};

struct Graph {
    int numNode;
    std::vector<std::vector<GraphSuccessor>> adj;
};

std::vector<GraphEdge> graphToEdgeList(const Graph& graph);

#endif
