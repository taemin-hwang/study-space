#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int V, E;
const int MAX_V = 401;
const int INF = 1000000;
int adj[MAX_V][MAX_V];
int dist[MAX_V][MAX_V];

int floyd() {
    for(int i = 1; i <= V; ++i) {
        for(int j = 1; j <= V; ++j) {
            if( i == j) dist[i][j] = 0;
            else if(adj[i][j] == -1) dist[i][j] = INF;
            else dist[i][j] = adj[i][j];
        }
    }

    for(int via = 1; via <= V; ++via) {
        for(int here = 1; here <= V; ++here) {
            for(int there = 1; there <= V; ++there) {
                if(dist[here][there] > dist[here][via] + dist[via][there]) {
                    dist[here][there] = dist[here][via] + dist[via][there];
                }
            }
        }
    }

    int min_dist = INT_MAX;

    for(int here = 1; here <= V; ++here) {
        for(int there = 1; there <= V; ++there) {
            int tmp_dist = dist[here][there];
            if(tmp_dist != INF && adj[there][here] != -1) {
                min_dist = min(min_dist, tmp_dist + adj[there][here]);
            }
        }
    }

    return min_dist;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> V >> E;
    int here, there, cost;

    memset(adj, -1, sizeof(adj));

    for(int i = 0; i < E; ++i) {
        cin >> here >> there >> cost;
        adj[here][there] = cost;
    }

    int min_dist = floyd();
    if(min_dist == INT_MAX) cout << -1 << endl;
    else cout << min_dist << endl;


}
