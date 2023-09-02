#include "nearest_neighbor.h"

#include <vector>
#include <numeric>
#include <iostream>

void nearest_neighbor(const Graph& graph) {
    std::vector<bool> visited(graph.numNode + 1);
    int current = 1;

    std::vector<int> optimalOrder{current};
    int optimalCost = 0;

    for (int iter = 0; iter < graph.numNode - 1; ++iter) {
        visited[current] = true;

        int minEdge = std::numeric_limits<int>::max();
        int next = -1;

        for (const auto& [neighbor, cost] : graph.adj[current]) {
            if (visited[neighbor]) continue;

            if (cost < minEdge) {
                minEdge = cost;
                next = neighbor;
            }
        }

        current = next;
        optimalOrder.push_back(current);
        optimalCost += minEdge;
    }


    for (const auto& [neighbor, cost] : graph.adj[current]) {
        if (neighbor == 1) {
            optimalCost += cost;
            break;
        }
    }

    std::cout << "Optimal order: ";
    for (const auto& node : optimalOrder) {
        std::cout << node << " ";
    }
}
