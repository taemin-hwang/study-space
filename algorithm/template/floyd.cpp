#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

int MAX_V = 1000;
int V; // number of vertexs
int adj[MAX_V][MAX_V]; // adjacent between vertexs (NOTE: adj should be 2d array in floyd)
int via[MAX_V][MAX_V]; // maxinum id in shortest path from u to v

void floyd() {
    // initialize diatance from i-th vertex to i-th vertex with 0 (same position)
    for(int i = 0; i < V; ++i) adj[i][i] = 0;
    memset(via, -1, sizeof(via));

    // @param
    // k: via, i: here, j: there
    for(int k =0; k < V; ++k) {
        for(int i = 0; i < V; ++i) {
            for(int j = 0; j < V; ++j) {
                // update distance[here][there], if distance[here][there] > distance[here][via] + distance[via][there]
                if(adj[i][j] > adj[i][k] + adj[k][j]) {
                    via[i][j] = k;
                    adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
    }
}

void reconstruct (int u, int v, vector<int>& path) {
    if(via[u][v] == -1) {
        path.push_back(u);
        if(u != v) path.push_back(v);
    } else {
        int w = via[u][v];
        reconstruct(u, w, path);
        path.pop_back();
        reconstruct(w, v, path);
    }
}

int main() {
}
