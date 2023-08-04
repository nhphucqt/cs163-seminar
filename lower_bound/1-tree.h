#ifndef ONETREE_H
#define ONETREE_H

#include "MST.h"

/// @brief Find lower bound of TSP by 1-tree --- O(VElog(V)
/// @param n number of nodes 
/// @param adj list of graph edges
/// @return 1-tree lower bound of TSP
int onetree_lowerbound(int n, std::vector<std::vector<GraphSuccessor>> &adj);

#endif