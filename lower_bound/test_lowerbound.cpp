#include "MST.h"
#include "1-tree.h"

#include <iostream>
//Uncomment to test

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<std::vector<GraphSuccessor>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, w; std::cin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }

    std::vector<GraphEdge> v;
    int ans = 0;
    //  Prim(n, adj, {}, v, ans);
    ans = onetree_lowerbound(n, adj);
    std::cout<<ans;
/* 
Input:
6 9
1 2 1
1 3 1
2 4 3
2 3 2
2 5 1
3 5 1
3 6 2
4 5 2
5 6 2

MST = 7
lowerbound = 10 */
}