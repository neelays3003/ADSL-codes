#include <iostream>
using namespace std;

#define MAX 10
#define INF 99999

void dijkstra(int graph[MAX][MAX], int n, int start){
    int dist[MAX];
    bool visited[MAX];
    int i,j;

    for(i = 0 ; i<n ; i++){
        dist[i] = INF;
        visited[i] = false;
    }

    dist[start] = 0;

    for(i = 0; i < n; i++){
        int min = INF;
        int u = -1;

        for(j = 0; j < n; j++){
            if(!visited[j] && dist[j] <= min){
                min = dist[j];
                u = j;
            }
        }
        if(u == -1) break;

        visited[u] = true;

        for(j = 0; j < n; j++){
            if(!visited[j] && graph[u][j] && dist[u] + graph[u][j] < dist[j]){
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    cout<<"Shortest path of all node from "<<start<<": "<<endl;
    for(i=0; i<n; i++){
        cout<<"To node "<<i<<": ";
        if(dist[i] == INF) cout<<"Unreachable"<<endl;
        else cout << dist[i] << endl;
    }
}

int main(){
    int graph[MAX][MAX];
    int start;
    int n;
    cout<<"Enter no. of vertex: ";
    cin>>n;
    cout<<"\nEnter adjacency matrix: ";
    for(int i =0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>graph[i][j];
        }
    }

    cout<<"\nEnter starting node: ";
    cin>>start;

    dijkstra(graph,n,start);
    return 0;
}