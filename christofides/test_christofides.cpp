#include <iostream>
#include "solver.h"

int main() {
    int numNode, numEdge;
    Graph graph;
    std::cin >> numNode >> numEdge;

    graph.numNode = numNode;
    graph.adj.assign(numNode + 1, std::vector<GraphSuccessor>());
    for (int i = 0; i < numEdge; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        addEdge(graph, GraphEdge{x,y,w});
    }
    
    std::vector<int> tspTour = solveTSP(graph);

    std::cout << "A TSP tour is: ";
    for (int u : tspTour) {
        std::cout << u << ' ';
    }

    return 0;
}

// Example:
// 6 15
// 1 2 27
// 1 3 17
// 1 4 31
// 1 5 33
// 1 6 20
// 2 3 14
// 2 4 14
// 2 5 34
// 2 6 38
// 3 4 25
// 3 5 38
// 3 6 34
// 4 5 22
// 4 6 34
// 5 6 22