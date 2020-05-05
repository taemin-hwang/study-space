#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

int V, E;
const int MAX_V = 10001;
vector<pair<int, int>> adj[MAX_V];

int prim() {
    // NOTE: V+1 must be used
    vector<bool> added(V+1, false);
    vector<int> parent(V+1, -1), minWeight(V+1, INT_MAX);

    int ret = 0;
    minWeight[1] = 0;
    parent[1] = 1;

    for(int iter = 0; iter < V; ++iter) {
        int u = -1;

        for(int v = 1; v <= V; ++v) {
            if(!added[v] && (u == -1 || minWeight[v] < minWeight[u])) {
                u = v;
            }
        }

        if(parent[u] != u) {
            // selected.push_back({parent[u], u});
        }

        added[u] = true;
        ret += minWeight[u];

        for(int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if(!added[v] && minWeight[v] > weight) {
                parent[v] = u;
                minWeight[v] = weight;
            }
        }

    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    int here, there, weight;

    cin >> V >> E;

    for(int i = 0; i < E; ++i) {
        cin >> here >> there >> weight;
        adj[here].push_back({there, weight});
        adj[there].push_back({here, weight});
    }

    cout << prim() << endl;
}
