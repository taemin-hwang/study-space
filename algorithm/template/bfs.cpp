#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> adj;

void bfs(int start, vector<int>& distance, vector<int>& parent) {
    distance = vector<int>(adj.size(), -1);
    parent = vector<int>(adj.size(), -1);

    queue<int> q;
    distance[start] = 0;
    parent[start] = start;
    q.push(start);

    while(!q.empty()) {
        int here = q.front();
        q.pop();

        for(int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i];

            if(distance[there] == -1) {
                q.push(there);
                distance[there] = distance[here] + 1;
                parent[there] = here;
            }
        }
    }
}

// caculate shortest path
vector<int> shortestPath(int v, const vector<int>& parent) {
    vector<int> path(1, v);
    while(parent[v] != v) {
        v = parent[v];
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void makeGraph() {
    adj.resize(9);
    adj['a'-'a'].push_back('b'-'a');
    adj['a'-'a'].push_back('d'-'a');
    adj['a'-'a'].push_back('e'-'a');
    adj['a'-'a'].push_back('h'-'a');
    adj['b'-'a'].push_back('a'-'a');
    adj['d'-'a'].push_back('a'-'a');
    adj['e'-'a'].push_back('a'-'a');
    adj['h'-'a'].push_back('a'-'a');

    adj['b'-'a'].push_back('d'-'a');
    adj['b'-'a'].push_back('c'-'a');
    adj['d'-'a'].push_back('b'-'a');
    adj['c'-'a'].push_back('b'-'a');

    adj['e'-'a'].push_back('f'-'a');
    adj['f'-'a'].push_back('e'-'a');

    adj['c'-'a'].push_back('f'-'a');
    adj['f'-'a'].push_back('c'-'a');
    adj['c'-'a'].push_back('g'-'a');
    adj['g'-'a'].push_back('c'-'a');

    adj['g'-'a'].push_back('i'-'a');
    adj['g'-'a'].push_back('d'-'a');
    adj['i'-'a'].push_back('g'-'a');
    adj['d'-'a'].push_back('g'-'a');
}

int main() {
    vector<int> parent, distance, shortest_path;

    makeGraph();

    bfs('a'-'a', distance, parent);

    shortest_path = shortestPath('i'-'a', parent);

    for(auto p : shortest_path)
        cout << (char)(p + 'a') << " -> ";
    cout << endl;

}
