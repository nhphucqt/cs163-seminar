#include "greedy.h"

#include <iostream>
#include <algorithm>
using namespace std;

// Find parent in DSU
int findPa(int u, vector<int>& pa) {
    if (u == pa[u]) return u;
    return pa[u] = findPa(pa[u], pa);
}

// Join DSU
bool join(int x, int y, vector<int> &pa, vector<int> &deg) {
    x = findPa(x, pa), y = findPa(y, pa);
    if (x == y) return false;
    if (deg[x] > deg[y]) swap(x, y);
    pa[x] = y;
    deg[y] += deg[x];
    return true;
}

void greedy_TSP(int n, std::vector<std::vector<GraphSuccessor>> &adj, std::vector<GraphEdge> &ans_edges, int &total_weight)
{   
    ans_edges.clear();
    total_weight = 0;
    vector<GraphEdge> edges;
    vector<int> pa(n + 1),
        degDSU(n + 1, 1), // degree of node in DSU 
        deg(n + 1); // degree of node in graph

    for (int i = 1; i <= n; ++i) pa[i] = i;

    for (int u = 1; u <= n; ++u) {
        for (auto e : adj[u]) {
            if (e.v < u) continue; // avoid duplicate edges
            edges.push_back({u, e.v, e.w});
        }
    }
    sort(edges.begin(), edges.end(), [&](GraphEdge &x, GraphEdge &y){ /* iterate from shortest edges */
        return make_pair(x.w, make_pair(x.u, x.v)) < make_pair(y.w, make_pair(y.u, y.v));
    });

    for (int loops = 1, i = 0; loops <= n; ++i) { // Add exactly n edges
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (deg[u] < 2 && deg[v] < 2 && (join(u, v, pa, degDSU) || loops == n)) {
            ++loops;
            ans_edges.push_back({u, v, w});
            total_weight += w;
            ++deg[u];
            ++deg[v];
        }
    }

    return;
}

// Uncomment to test

// int main() {
//     int n, m; std::cin >> n >> m;
//     std::vector<std::vector<GraphSuccessor>> adj(n + 1);
//     for (int i = 0; i < m; ++i) {
//         int x, y, w; std::cin >> x >> y >> w;
//         adj[x].push_back({y, w});
//         adj[y].push_back({x, w});
//     }

//     std::vector<GraphEdge> v;
//     int ans = 0;
//     greedy_TSP(n, adj, v, ans);
//     std::cout<<"Total weight = " << ans << '\n';

//     std::cout << "Edges: \n";
//     for (auto e : v) std::cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
    
// /* Input:
// 4 6
// 1 2 3
// 2 3 4
// 1 3 2
// 2 4 5
// 1 4 3
// 3 4 1

// Output: 
// Total weight = 11
// Edges: 
// 3 4 1
// 1 3 2
// 1 2 3
// 2 4 5 */
// } 