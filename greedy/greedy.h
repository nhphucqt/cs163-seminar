#ifndef GREEDY_H
#define GREEDY_H

#include "Graph.h"

/// @brief Find a TSP tour by greedy heuristic
/// @param n number of nodes 
/// @param adj list of graph edges
/// @param ans_edges list of edges in MST found, initially empty
/// @param total_weight total weight in TSP tour found, initially 0
void greedy_TSP(int n, std::vector<std::vector<GraphSuccessor>> &adj, std::vector<GraphEdge> &ans_edges, int &total_weight);

#endif