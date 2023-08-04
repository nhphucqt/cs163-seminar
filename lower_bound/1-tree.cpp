#include "1-tree.h"

int onetree_lowerbound(int n, std::vector<std::vector<GraphSuccessor>> &adj)
{   
    int ans = 0;
    std::vector<GraphEdge> ans_edges; // only for passing in Prim function

    // Find 2 shortest edges connected to u ---- O(V + E)
    auto findMinEdges = [&](int u) { 
        int min1 = 1e9, min2 = 1e9;
        for (GraphSuccessor e : adj[u]) {
            if (e.w <= min1) {min2 = min1; min1 = e.w;}
            else if (e.w < min2) min2 = e.w;
        }
        return min1 + min2;
    };
    
    for (int i = 1; i <= n; ++i) {
        int MST_weight = 0;
        Prim(n, adj, {i}, ans_edges, MST_weight);
        for (int x = 1; x <= n; ++x) if (x != i) {
            ans = std::max(ans, MST_weight + findMinEdges(i));
        }
    }
    return ans;
}
