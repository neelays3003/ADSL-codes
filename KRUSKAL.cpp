#include <iostream>
using namespace std;

#define MAX 100

struct Edge {
    int u, v, weight;
};

string dept[MAX];
Edge edges[MAX];
int parent[MAX];

// Find the root of a node 
int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

// Union of two sets
void union_set(int a, int b) {
    parent[find(a)] = find(b);
}

// Bubble sort edges by weight
void sortEdges(int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal's algorithm
void kruskal(int nodeCount, int edgeCount) {
    for (int i = 0; i < nodeCount; i++){
        parent[i] = i;
    }

    sortEdges(edgeCount);

    int totalCost = 0;
    cout << "\nMinimum Spanning Tree:\n";

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (find(u) != find(v)) {
            union_set(u, v);
            cout << dept[u] << " - " << dept[v] << ": " << w << "\n";
            totalCost += w;
        }
    }

    cout << "Total cost: " << totalCost << "\n";
}

int main() {
    int n, e;

    cout << "Enter number of departments: ";
    cin >> n;

    cout << "Enter department names:\n";
    for (int i = 0; i < n; i++) {
        cout << "Department " << i << ": ";
        cin >> dept[i];
    }

    cout << "Enter number of connections: ";
    cin >> e;

    cout << "Enter connections (u v weight):\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskal(n, e);

    return 0;
}