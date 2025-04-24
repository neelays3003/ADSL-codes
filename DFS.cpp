#include <iostream>
using namespace std;

#define MAX_NODES 100 

class Graph {
    int adj[MAX_NODES][MAX_NODES]; 
    int V; 
public:
    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = 0; 
    }

    void addEdge(int u, int v) {
        if (u >= V || v >= V || u < 0 || v < 0) {
            cout << "Invalid edge!\n";
            return;
        }
        adj[u][v] = 1;
        adj[v][u] = 1; 
    }

    void DFS(int start){
        if(start >= V || start < 0){
            cout << "Invalid starting node"<<endl;
            return;
        }

        int visited[MAX_NODES] = {0};
        int stack[MAX_NODES];
        int top = -1;

        stack[++top] = start;

        while(top >= 0){
            int node = stack[top--];
            if(visited[node] == 0){
                visited[node] = 1;
                cout<< node << " ";
            }

            for(int i = 0; i< V; i++){
                if(adj[node][i] == 1 && visited[i] == 0){
                    stack[++top] = i;
                }
            }
        }
    }
};

int main() {
    int vertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;
    Graph g(vertices);

    int choice;
    do {
        cout << "\n--- Graph Menu ---\n";
        cout << "1. Add Edge\n";
        cout << "2. Perform DFS\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v;
                cout << "Enter two vertices to add an edge (u v): ";
                cin >> u >> v;
                g.addEdge(u, v);
                break;
            }
            case 2: {
                int start;
                cout << "Enter the starting vertex for DFS: ";
                cin >> start;
                cout << "DFS starting from node " << start << ": ";
                g.DFS(start);
                break;
            }
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}