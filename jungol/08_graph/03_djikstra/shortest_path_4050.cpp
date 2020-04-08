#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <functional>
#include <queue>

using namespace std;

int n, m;
vector<vector<pair<int, long long>>> adj;

long long djikstra() {
    long long shortest_path;
    vector<long long> dist;
    dist.resize(n+1);

    priority_queue<pair<long long, int>> pq;

    pq.push({0, 1});
    dist[1] = 0;

    while(!pq.empty()) {
        long long cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        //cout << here << endl;
        //getchar();

        if(dist[here] < cost) continue;

        for(int i = 0; i < adj[here].size(); ++i) {
            long long weight = adj[here][i].second;
            int there = adj[here][i].first;
            int newCost = cost + weight;

            //cout << here << ", " << there << " " << newCost << endl;
            if(dist[there] == 0 || dist[there] > newCost) {
                dist[there] = newCost;
                pq.push({-newCost, there});
            }
        }
    }

    shortest_path = dist[n];

    return shortest_path;
}

int main() {
    cin >> n >> m;
    adj.resize(n+1);
    int here, there;
    long long weight;

    for(int i = 0; i < m ; i++) {
        cin >> here >> there >> weight;
        adj[here].push_back({there, weight});
    }

    cout << djikstra() << endl;
}
