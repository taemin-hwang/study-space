#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>

using namespace std;

int V;
int MAX_V;
vector<pair<int, int>> adj[MAX_V];

// bellman ford can get a shortest distance
// it can be applied in case graph has negative wegiht
vector<int> bellmanFord(int src) {
    vector<int> upper(V, INF);
    upper[src] = 0;
    bool updated;

    // iterate V-times for updating shortest distance
    for(int iter = 0; iter < V; ++iter) {
        updated = false;
        // update distance of every vertex
        for(int here = 0; here < V; ++here) {
            for(int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;

                // update distance when distance[there] > distance[here] + weight[here][there]
                if(upper[there] > upper[here] + cost) {
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }

    if(updated) upper.clear;
    return upper;
}

int main() {

}
