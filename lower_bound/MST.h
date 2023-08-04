#ifndef MST_H
#define MST_H

#include "Graph.h"
#include <set>

bool operator < (const GraphSuccessor &x, const GraphSuccessor &y);


/// @brief Prim's Algorithm --- O(Elog(V))
/// @param n number of nodes 
/// @param adj list of graph edges
/// @param exclude_nodes list of excluded nodes
/// @param ans_edges list of edges in MST found, initially empty
/// @param total_weight total weight in MST found, initially 0
void Prim(int n, std::vector<std::vector<GraphSuccessor>> &adj, std::vector<int> exclude_nodes, std::vector<GraphEdge> &ans_edges, int &total_weight);

#endif