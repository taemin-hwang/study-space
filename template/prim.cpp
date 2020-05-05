#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

using namespace std;

const int MAX_V = 100;
const int INF = INT_MAX;

int V;

vector<pair<int, int>> adj[MAX_V];

// @param selected MST tree
int prim(vector<pair<int, int>>& selected) {
    selected.clear();

    // cache for checking if vertex is added to MST or not
    vector<bool> added(V, false);

    vector<int> minWeight(V, INF), parent(V, -1);

    int ret = 0;

    minWeight[0] = parent[0] = 0;

    // iterate for number of vertex
    for(int iter = 0; iter < V; ++iter) {
        int u = -1;

        // 1. find vertex u having minimum weight
        for(int v = 0; v < V; ++v) {
            if(!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
                u = v;
        }

        if(parent[u] != u) {
            selected.push_back(make_pair(parent[u], u));
        }

        // 2. add vertex u to MST
        ret += minWeight[u];
        added[u] = true;

        // 3. update parent, minWeight after adding vertex u to MST
        for(int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first, weight = adj[u][i].second;
            if(!added[v] && minWeight[v] > weight) {
                parent[v] = u;
                minWeight[v] = weight;
            }
        }

    }


}

int main() {
    ios_base::sync_with_stdio(false);

}
