#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

class GraphEdge {
public:
    int u, v, w;

    GraphEdge();
    GraphEdge(int u, int v, int w);
};

class GraphSuccessor {
public:
    int u, w;

    GraphSuccessor();
    GraphSuccessor(int u, int w);
};

// Graph Class
// has numNode nodes indexed from 1 to numNode
// has a vector of edges (GraphEdge)
class Graph {
public:
    int numNode;
    std::vector<GraphEdge> edges;

    Graph();
    Graph(int numNode, const std::vector<GraphEdge>& edges);
};

class UndirectedGraph : public Graph {
public:
    std::vector<std::list<GraphSuccessor>> adj;

    UndirectedGraph();
    UndirectedGraph(int numNode, const std::vector<GraphEdge>& edges);
};

class DirectedGraph : public Graph {
public:
    std::vector<std::list<GraphSuccessor>> adj;

    DirectedGraph();
    DirectedGraph(int numNode, const std::vector<GraphEdge>& edges);
};

#endif