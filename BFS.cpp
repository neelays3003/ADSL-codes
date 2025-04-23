#include <iostream>
using namespace std;
#define max_nodes 100

class Graph{
    public:
    int adj[max_nodes][max_nodes];
    int V;
    Graph(int vertices){
        V = vertices;
        for(int i = 0; i< V; i++){
            for(int j=0; j<V; j++){
                adj[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v){
        if(u >= V || v >= V || u < 0 || v < 0){
            cout << "Invalid nodes"<<endl;
            return;
        }
        adj[u][v] = 1;
        adj[v][u] = 1;
    }


    void BFS(int start){
        int visited[max_nodes] = {0};
        int queue[max_nodes];
        int front = 0, rear = 0;

        visited[start] = 1;
        queue[rear++] = start;

        while(front < rear){
            int node = queue[front++];
            cout << node << " ";
            for(int i = 0; i < V; i++){
                if(adj[node][i] == 1 && visited[i] == 0){
                    visited[i] = 1;
                    queue[rear++] = i;
                }
            }
        }
        cout<<endl;
    }
};


int main(){
    int vertices;
    cout<<"Enter no. of vertices: ";
    cin>>vertices;
    Graph g(vertices);
    
    int choice;
    do{
        cout<<endl<<"-----------BFS Traversal------------"<<endl;
        cout<<"1. Add Edges"<<endl;
        cout<<"2. Perform BFS"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"enter choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                int u,v;
                cout << "Enter edges(u v): ";
                cin >> u >> v;
                g.addEdge(u,v);
                break;
            }

            case 2:{
                int start;
                cout << "Enter starting point: ";
                cin >> start;
                g.BFS(start);
                break;
            }

            case 3:{
                cout <<"Exiting..."<<endl;
                break;
            }

            default:{
                cout<<"Invalid choice.";
            }
        }
    }while(choice != 3);
}