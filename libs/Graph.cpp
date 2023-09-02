#include "Graph.h"

std::vector<GraphEdge> graphToEdgeList(const Graph& graph) {
    std::vector<GraphEdge> edges;

    for (int u = 1; u <= graph.numNode; ++u) {
        for (const auto& [v, w] : graph.adj[u]) {
            // there exists {u, v, w} and {v, u, w}
            // we only consider one of them
            if (u < v) {
                edges.push_back({u, v, w});
            }
        }
    }

    return edges;
}

std::vector<std::vector<int>> graphToAdjMatrix(const Graph& graph) {
    std::vector adjMatrix(graph.numNode + 1, std::vector(graph.numNode + 1, 0));

    for (int u = 1; u <= graph.numNode; ++u) {
        for (const auto& [v, w] : graph.adj[u]) {
            adjMatrix[u][v] = w;
        }
    }

    return adjMatrix;
}
