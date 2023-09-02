#include "naive.h"

#include <numeric>
#include <algorithm>
#include <vector>
#include <iostream>

int calcDist(const std::vector<std::vector<int>>& adjMatrix,
             const std::vector<int>& order) {
    int dist = 0;
    int prev = 1;
    for (int node : order) {
        dist += adjMatrix[prev][node];
        prev = node;
    }
    dist += adjMatrix[prev][1];
    return dist;
}

void naive(const Graph& graph) {
    std::vector<int> order(graph.numNode - 1);
    std::vector<int> optimalOrder(graph.numNode - 1);
    int optimalDist = std::numeric_limits<int>::max();

    auto adjMatrix = graphToAdjMatrix(graph);

    std::iota(order.begin(), order.end(), 2);

    do {
        int dist = calcDist(adjMatrix, order);

        if (dist < optimalDist) {
            optimalDist = dist;
            optimalOrder = order;
        }
    } while (std::next_permutation(order.begin(), order.end()));

    std::cout << "Optimal order: " << 1 << " ";
    for (int node : optimalOrder) {
        std::cout << node << " ";
    }
}

