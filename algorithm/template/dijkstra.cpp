#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <map>

using namespace std;

#define MAX_V = 10;
int V; // num of vertexs
vector<pair<int, int>> adj[MAX_V]; // there, weight

vector<int> dijkstra(int src) {
    vector<int> dist(V, INT_MAX); // initialize distance of each vertex with INF
    dist[src] = 0;

    priority_queue<pair<int,int>> pq;
    pq.push({0, src});

    while(!pq.empty()) {
        int cost = -pq.top().first; // -pq.top().first should be used because stored value is negative
        int here = pq.top().second;
        pq.pop();

        if(dist[here] < cost) continue;
        for(int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;

            if(dist[there] > nextDist) { // update distance if new distance is shorter than previous distance
                dist[there] = nextDist;
                pq.push({-nextDist, there}); // NOTE: -nextDist should be used for prority queue
            }
        }
    }
}

int main() {


}
