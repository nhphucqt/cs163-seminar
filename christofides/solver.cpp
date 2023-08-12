#include "solver.h"

bool cmp::operator()(const GraphEdge& a, const GraphEdge& b) {
    return a.w > b.w;
}

void addEdge(Graph& graph, const GraphEdge& edge) {
    graph.adj[edge.u].push_back({edge.v, edge.w});
    graph.adj[edge.v].push_back({edge.u, edge.w});
}

void findMST(const Graph& graph, Graph& mst) {
    HeapMin heapMin;
    std::vector<bool> mark(graph.numNode+1, false);
    mst.numNode = graph.numNode;
    mst.adj.assign(graph.numNode + 1, std::vector<GraphSuccessor>());
    mark[1] = true;
    for (GraphSuccessor succ : graph.adj[1]) {
        heapMin.push({1, succ.v, succ.w});
    }
    while (!heapMin.empty()) {
        GraphEdge edge = heapMin.top();
        heapMin.pop();
        if (mark[edge.v]) {
            continue;
        }
        addEdge(mst, edge);
        mark[edge.v] = true;
        for (GraphSuccessor succ : graph.adj[edge.v]) {
            heapMin.push({edge.v, succ.v, succ.w});
        }
    }
}

std::vector<int> findOddDegreeVertices(const Graph& graph) {
    std::vector<int> nodes;
    for (int i = 1; i <= graph.numNode; ++i) {
        if (graph.adj[i].size() % 2 != 0) {
            nodes.push_back(i);
        }
    }
    return nodes;
}

std::vector<GraphEdge> getMinimumWeightMaxMatching(const Graph& graph) {
    // Turn to 0-indexed graph
    std::vector<GraphEdge> edgesList = graphToEdgeList(graph);
    PerfectMatching::Options options;
    int* edges = new int[2*edgesList.size()];
    int* weights = new int[edgesList.size()];
    for (int i = 0; i < (int)edgesList.size(); ++i) {
        edges[i*2] = edgesList[i].u - 1;
        edges[i*2+1] = edgesList[i].v - 1;
        weights[i] = edgesList[i].w;
    }
    PerfectMatching *pm = new PerfectMatching(graph.numNode, edgesList.size());
    for (int i = 0; i < (int)edgesList.size(); ++i) {
        pm->AddEdge(edges[i*2], edges[i*2+1], weights[i]);
    }
    pm->options = options;
    pm->Solve();

    std::vector<GraphEdge> matchedEdges;
    for (int i = 0; i < (int)edgesList.size(); ++i) {
        if (pm->GetSolution(i)) {
            matchedEdges.push_back({edgesList[i].u, edgesList[i].v, edgesList[i].w});
        }
    }
    delete[] edges;
    delete[] weights;
    return matchedEdges;
}

void combineGraphs(const Graph& a, const Graph& b, Graph& c) {
    c.numNode = std::max(a.numNode, b.numNode);
    c.adj.assign(c.numNode + 1, std::vector<GraphSuccessor>());
    std::vector<GraphEdge> edgesA = graphToEdgeList(a);
    std::vector<GraphEdge> edgesB = graphToEdgeList(b);
    for (int i = 0; i < (int)edgesA.size(); ++i) {
        addEdge(c, edgesA[i]);
    }
    for (int i = 0; i < (int)edgesB.size(); ++i) {
        addEdge(c, edgesB[i]);
    }
}

void findEulerianCircuit(int u, std::vector<GraphEdge>& edges, std::vector<std::vector<int>>& adj, std::vector<int>& cur, std::vector<bool>& mark, std::vector<int>& eulerCircuit) {
    for (; cur[u] < (int)adj[u].size(); ++cur[u]) {
        int e = adj[u][cur[u]];
        if (!mark[e]) {
            int v = edges[e].u ^ edges[e].v ^ u;
            mark[e] = true;
            findEulerianCircuit(v, edges, adj, cur, mark, eulerCircuit);
        }
    }
    eulerCircuit.push_back(u);
}

std::vector<int> findEulerianCircuit(const Graph& graph) {
    std::vector<GraphEdge> edges = graphToEdgeList(graph);
    std::vector<std::vector<int>> adj(graph.numNode+1, std::vector<int>());
    std::vector<int> cur(graph.numNode+1, 0);
    std::vector<bool> mark(edges.size(), false);
    for (int i = 0; i < (int)edges.size(); ++i) {
        adj[edges[i].u].push_back(i);
        adj[edges[i].v].push_back(i);
    }
    std::vector<int> eulerCircuit;
    findEulerianCircuit(1, edges, adj, cur, mark, eulerCircuit);
    return eulerCircuit;
}

std::vector<int> findHamiltonianCircuitFromEulerianCircuit(int numNode, std::vector<int> eulerCircuit) {
    std::vector<bool> mark(numNode+1, false);
    std::vector<int> hamiltonCircuit;
    for (int i = 0; i < (int)eulerCircuit.size(); ++i) {
        if (!mark[eulerCircuit[i]]) {
            mark[eulerCircuit[i]] = true;
            hamiltonCircuit.push_back(eulerCircuit[i]);
        }
    }
    hamiltonCircuit.push_back(hamiltonCircuit[0]);
    return hamiltonCircuit;    
}

std::vector<int> solveTSP(const Graph& graph) {
    // Find the minimum spanning tree
    Graph mst;
    findMST(graph, mst);


    // Find odd degree vertices in mst
    std::vector<int> oddDegreeVertices = findOddDegreeVertices(mst);
    std::vector<int> mark(mst.numNode + 1, -1);
    for (int i = 0; i < (int)oddDegreeVertices.size(); ++i) {
        mark[oddDegreeVertices[i]] = i;
    }
    
    // Create a new graph for finding minimum weight perfect matching
    Graph matchingGraph;
    matchingGraph.numNode = oddDegreeVertices.size();
    matchingGraph.adj.assign(matchingGraph.numNode + 1, std::vector<GraphSuccessor>());
    for (int i = 0; i < (int)oddDegreeVertices.size(); ++i) {
        int u = oddDegreeVertices[i];
        for (GraphSuccessor succ : graph.adj[u]) {
            if (mark[succ.v] != -1) {
                matchingGraph.adj[i+1].push_back({mark[succ.v] + 1, succ.w});
            }
        }
    }

    // Find minimum weight perfect matching in matchingGraph
    std::vector<GraphEdge> minWMaching = getMinimumWeightMaxMatching(matchingGraph);
    for (int u = 1; u <= matchingGraph.numNode; ++u) {
        matchingGraph.adj[u].clear();
    }
    for (int i = 0; i < (int)minWMaching.size(); ++i) {
        addEdge(matchingGraph, minWMaching[i]);
    }

    // Turn the matchingGraph back to the original form
    std::vector<std::vector<GraphSuccessor>> orgAdj(mst.numNode+1, std::vector<GraphSuccessor>());
    for (int u = 1; u <= matchingGraph.numNode; ++u) {
        for (GraphSuccessor succ : matchingGraph.adj[u]) {
            orgAdj[oddDegreeVertices[u - 1]].push_back({oddDegreeVertices[succ.v - 1], succ.w});
        }
    }
    matchingGraph.numNode = mst.numNode;
    matchingGraph.adj.swap(orgAdj);

    // Combine mst and matchingGraph into a new graph to find Eulerian circuit
    Graph eulerGraph;
    combineGraphs(mst, matchingGraph, eulerGraph);


    // Find the Eulerian circuit in eulerGraph
    std::vector<int> eulerCircuit = findEulerianCircuit(eulerGraph);

    // Construct the Hamiltonian circuit from eulerCircuit
    std::vector<int> hamiltonCircuit = findHamiltonianCircuitFromEulerianCircuit(eulerGraph.numNode, eulerCircuit);

    return hamiltonCircuit;
}