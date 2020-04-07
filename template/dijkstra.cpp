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
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int,int>> pq;
    pq.push({0, src});

    while(!pq.empty()) {
        int cost = -pq.top().first; // diff top() from front() of queue
        int here = pq.top().second;
        pq.pop();

        if(dist[here] < cost) continue;
        for(int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;

            if(dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push({-nextDist, there});
            }

        }

    }

}

int main() {


}
