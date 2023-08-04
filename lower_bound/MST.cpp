#include "MST.h"
// #include <bits/stdc++.h>
// using namespace std;

bool operator < (const GraphSuccessor &x, const GraphSuccessor &y) {
    return std::make_pair(x.w, x.v) < std::make_pair(y.w, y.v);
}

void Prim(int n, std::vector<std::vector<GraphSuccessor>> &adj, std::vector<int> exclude_nodes, std::vector<GraphEdge> &ans_edges, int &total_weight) {
    const int INF = 1000000000;

    total_weight = 0;
    ans_edges.clear();

    std::vector<GraphSuccessor> min_e(n + 2, {-1, INF});
    std::set<GraphSuccessor> q;
    std::vector<bool> selected(n + 2, false), excluded(n + 2, false);
    for (int i : exclude_nodes) excluded[i] = 1;
    for (int i = 1; i <= n; ++i) if (!excluded[i]) {
        q.insert({i, 0});
        min_e[i].w = 0;
        break;
    }

    for (int i = 0; i < n - (int)exclude_nodes.size(); ++i) {
        if (q.empty()) {
            // No MST
            total_weight = -1;
            ans_edges.clear();
            return;
        }

        int u = q.begin()->v;
        int weight = q.begin()->w;
        selected[u] = true;
        total_weight += weight;
        q.erase(q.begin());

        if (min_e[u].v != -1)
            ans_edges.push_back({u, min_e[u].v, weight});

        for (GraphSuccessor e : adj[u]) {
            if (!excluded[e.v] && !selected[e.v] && e.w < min_e[e.v].w) {
                q.erase({e.v, min_e[e.v].w});
                min_e[e.v] = {u, e.w};
                q.insert({e.v, e.w});
            }
        }
    }

    return;
}