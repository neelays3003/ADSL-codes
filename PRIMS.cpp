#include<iostream>
using namespace std;

const int s = 100;
const int inf = 99999;

int graph[s][s];
string department[s];

int minkey(int key[],bool mstset[], int n){
    int min = inf, minindex = -1;
    for(int i=0; i<n; i++){
        if(!mstset[i] && key[i] < min){
            min = key[i];
            minindex = i;
        }
    }
    return minindex;
}

void prims(int n){
    int key[s];
    int parent[s];
    bool mstset[s];

    for(int i = 0; i < n; i++){
        key[i] = inf;
        mstset[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < n-1; count++){
        int u = minkey(key, mstset, n);
        mstset[u] = true;

        for(int v =0; v<n; v++){
            if(graph[u][v] != 0 && !mstset[v] && graph[u][v] < key[v]){
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    //printing
    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    int totalcost = 0;
    for (int i = 1; i < n; i++) {
        cout << department[parent[i]] << " - " << department[i] << " : " << graph[i][parent[i]] << endl;
        totalcost += graph[i][parent[i]];
    }
    cout << "Total distance: " << totalcost << endl;
}


int main(){
    int n;
    cout<<"Enter the number of department: ";
    cin>>n;
    cout<<"Enter names of department: "<<endl;
    for (int i = 0; i < n; i++) {
        cout << "Department " << i << ": ";
        cin >> department[i];
    }

    cout << "Enter the distance (0 for same  and 99999 if not connected)"<<endl;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout << "From department " << department[i] << " and " << department[j]<< " : ";
            cin >> graph[i][j];
        }
    }

    prims(n);
    return 0;
}