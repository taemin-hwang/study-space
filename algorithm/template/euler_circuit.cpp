#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<int>> adj;

void MakeGraph() {
    adj.resize(8);
    for(int i = 0 ; i < adj.size(); i++) adj[i].resize(8);
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[3][5] = 1;
    adj[3][4] = 1;
    adj[4][0] = 1;
    adj[5][6] = 1;
    adj[6][7] = 1;
    adj[7][3] = 1;
}

void getEulerCircuit(int here, vector<int>& circuit) {
    for(int there = 0; there < adj[here].size(); there++) {
        if(adj[here][there] > 0) {
            adj[here][there] = 0;
            adj[there][here] = 0;
            getEulerCircuit(there, circuit);
        }
    }

    circuit.push_back(here);
}

int main() {
    vector<int> circuit;
    MakeGraph();
    getEulerCircuit(0, circuit);
    reverse(circuit.begin(), circuit.end());

    for(auto p : circuit)
        cout << p << endl;
}
