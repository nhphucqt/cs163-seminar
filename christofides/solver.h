#ifndef CHRISTOFIDES_SOLVER_H
#define CHRISTOFIDES_SOLVER_H

#include <vector>
#include <queue>
#include <iostream>
#include "Graph.h"
#include "PerfectMatching.h"

#define HeapMin std::priority_queue<GraphEdge, std::vector<GraphEdge>, cmp>

struct cmp {
    bool operator () (const GraphEdge& a, const GraphEdge& b);
};

void addEdge(Graph& graph, const GraphEdge& edge);

void findMST(const Graph& graph, Graph& mst);

std::vector<int> findOddDegreeVertices(const Graph& graph);

std::vector<GraphEdge> getMinimumWeightMaxMatching(const Graph& graph);

void combineGraphs(const Graph& a, const Graph& b, Graph& c);

void findEulerianCircuit(int u, std::vector<GraphEdge>& edges, std::vector<std::vector<int>>& adj, std::vector<int>& cur, std::vector<bool>& mark, std::vector<int>& eulerCircuit);

std::vector<int> findEulerianCircuit(const Graph& graph);

std::vector<int> findHamiltonianCircuitFromEulerianCircuit(int numNode, std::vector<int> eulerCircuit);

std::vector<int> solveTSP(const Graph& graph);

#endif