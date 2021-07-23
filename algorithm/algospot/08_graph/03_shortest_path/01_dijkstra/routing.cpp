#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int m, n;
vector<pair<int, double>> adj[10001];
double dist[10001];

double djikstra(int src) {
    double min_path = 0;

    dist[src] = 1;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, src});
    //pq.push({1, src});

    while(!pq.empty()) {
        double cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if(dist[here] != 0 && dist[here] < cost) continue;

        for(int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            double nextNoise = cost + log2(adj[here][i].second);
            //double nextNoise = cost * adj[here][i].second;

            if(dist[there] == 0 || nextNoise < dist[there]) {
                //cout << there << ", " << nextNoise << endl;
                dist[there] = nextNoise;
                pq.push({nextNoise, there});
            }
        }
    }

    min_path = dist[n-1];
    return min_path;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    int here, there;
    double min_noise = 1;
    double noise;
    vector<double> ans;
    cin >> t;

    for(int i = 0; i < t; i++) {
        cin >> n >> m;

        for(int i = 0 ; i < m; i++) {
            cin >> here >> there >> noise;
            adj[here].push_back({there, noise});
            adj[there].push_back({here, noise});
        }

        ans.push_back(pow(2, djikstra(0)));
    }
    cout.precision(11);
    for(auto p : ans) {
        cout << p << endl;
    }

}
