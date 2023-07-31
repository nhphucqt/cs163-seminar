#include "Graph.h"

GraphEdge::GraphEdge() = default;

GraphEdge::GraphEdge(int u, int v, int w) : u(u), v(v), w(w) {}

GraphSuccessor::GraphSuccessor() = default;

GraphSuccessor::GraphSuccessor(int u, int w) : u(u), w(w) {}

Graph::Graph() : numNode(0) {}

Graph::Graph(int numNode, const std::vector<GraphEdge>& edges) : numNode(numNode), edges(edges) {}

UndirectedGraph::UndirectedGraph() : Graph() {}

UndirectedGraph::UndirectedGraph(int numNode, const std::vector<GraphEdge>& edges) : Graph(numNode, edges) {
    adj.assign(edges.size(), std::list<GraphSuccessor>());
    for (int i = 0; i < (int)edges.size(); ++i) {
        adj[edges[i].u].emplace_back(edges[i].v, edges[i].w);
        adj[edges[i].v].emplace_back(edges[i].u, edges[i].w);
    }
}

DirectedGraph::DirectedGraph() : Graph() {}

DirectedGraph::DirectedGraph(int numNode, const std::vector<GraphEdge>& edges) : Graph(numNode, edges) {
    adj.assign(edges.size(), std::list<GraphSuccessor>());
    for (int i = 0; i < (int)edges.size(); ++i) {
        adj[edges[i].u].emplace_back(edges[i].v, edges[i].w);
    }
}