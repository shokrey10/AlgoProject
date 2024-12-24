#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Disjoint Set Union (Union-Find) structure
class DisjointSet {
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

// Function to compare edges based on their weights
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to implement Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int numVertices) {
    sort(edges.begin(), edges.end(), compareEdges); // Sort edges by weight

    DisjointSet ds(numVertices);
    vector<Edge> mst; // To store the resulting MST

    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;

        // If including this edge does not cause a cycle
        if (ds.find(u) != ds.find(v)) {
            mst.push_back(edge); // Add it to the MST
            ds.unionSets(u, v);   // Union the sets
        }
    }

    return mst;
}

// Main function to demonstrate Kruskal's algorithm
int main() {
    int numVertices = 4; // Number of vertices in the graph
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    vector<Edge> mst = kruskalMST(edges, numVertices);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }

    return 0;
}
