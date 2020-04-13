#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int n, INF = 1000000000;
vector<pair<int, int>> adj[501];

vector<long long> dist, last_dist;

bool bellman_ford() {
    dist.resize(n+1);
    for(int there = 1; there <= n; ++there) {
        dist[there] = INF;
    }

    dist[1] = 0;

    bool updated = false;

    for(int iter = 1; iter <= n; ++iter) {
        for(int here = 1; here <= n; ++here) {
            for(int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;

                // NOTE: need to insert dist[here] != INF
                if(dist[here] != INF && dist[there] > dist[here] + cost) {
                    dist[there] = dist[here] + cost;
                    if(iter == n) updated = true;
                }
            }
        }
    }

    if(updated) return false;

    for(int i = 2; i <= n; ++i) {
        if(dist[i] >= INF) {
            dist[i] = -1;
        }
    }
    return true;
}

int main() {
    int m, here, there, weight;

    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        cin >> here >> there >> weight;
        adj[here].push_back({there, weight});
    }

    bool ret = bellman_ford();
    if(!ret) cout << -1 << endl;
    else {
        for(int there = 2; there <= n; ++there) {
            cout << dist[there] << endl;
        }
    }

}
