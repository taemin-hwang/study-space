#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <queue>
#include <climits>

using namespace std;

/*
    dijkstra
     - find the shortest path in a weighted graph
     - use the priority queue, and memoization the path cost

    graph => vector<vector<pair<int, int>>
     - (u => {v1, w1}, {v2, w2}, ...)

    memo => vector<int>
     - memo[i] => stores the min path cost from i to end

    priority_queue(pair<int, int>) <= dist, node
*/


int dijkstra(int n, vector<vector<pair<int, int>>>& graph, int start, int end) {

    vector<int> memo(n, INT_MAX);
    vector<int> prev(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> mq;

    // push the starting point
    // CHECK POINT: push(0, start) <= from start, to start, distance: 0
    mq.push({0, start});

    while(!mq.empty()) {

        int qsize = mq.size();

        for(int i = 0 ; i < qsize; i++) {
            auto [dist, from] = mq.top(); // read top priority

            mq.pop(); // remove the top
            if(dist > memo[from]) continue;

            if(from == end) break;

            auto children = graph[from];

            for(auto child : children) {
                auto [to, weight] = child;

                // std::cout << from << "->" << to << "(" << weight << ") + " << dist << std::endl;

                if(dist + weight < memo[to]) {
                    mq.push({dist + weight, to});
                    memo[to] = dist + weight;
                    prev[to] = from;
                }

            }
        }
    }

    /*
        -1 0 1
        curr <- prev[2] = 1
        curr <- prev[1] = 0
        curr <- prev[0] = -1
    */

    // 🔍 경로 복원 및 디버깅 출력
    if (memo[end] < INT_MAX) {
        int curr = end;
        vector<int> seen;
        cout << "Path: ";
        while (curr != -1) {
            if (find(seen.begin(), seen.end(), curr) != seen.end()) {
                cout << "(cycle at " << curr << ")";
                break;
            }
            seen.push_back(curr);
            cout << curr << " ";
            curr = prev[curr];
            if (curr != -1) cout << "<- ";
        }
        cout << endl;
    }

    // CHECK POINT: memo[end] <= from start, to end, return distance
    return memo[end] == INT_MAX ? -1 : memo[end];
}


/*
    0 -> 1 (1)
    1 -> 2 (2)
    0 -> 2 (5)
*/

int main() {
    // Test 1: Simple triangle graph
    int n = 3;
    vector<vector<pair<int, int>>> graph1(n);
    graph1[0].push_back({1, 1});
    graph1[1].push_back({2, 2});
    graph1[0].push_back({2, 5});
    cout << "Test 1 (Expected 3): " << dijkstra(n, graph1, 0, 2) << endl;

    // Test 2: Disconnected node
    n = 4;
    vector<vector<pair<int, int>>> graph2(n);
    graph2[0].push_back({1, 1});
    graph2[1].push_back({2, 1});
    cout << "Test 2 (Expected -1): " << dijkstra(n, graph2, 0, 3) << endl;

    // Test 3: Multiple paths
    n = 5;
    vector<vector<pair<int, int>>> graph3(n);
    graph3[0].push_back({1, 10});
    graph3[0].push_back({2, 3});
    graph3[2].push_back({1, 1});
    graph3[1].push_back({3, 2});
    graph3[2].push_back({3, 8});
    graph3[3].push_back({4, 7});
    cout << "Test 3 (Expected 13): " << dijkstra(n, graph3, 0, 4) << endl;

    // Test 4: Cycle
    n = 4;
    vector<vector<pair<int, int>>> graph4(n);
    graph4[0].push_back({1, 1});
    graph4[1].push_back({2, 1});
    graph4[2].push_back({0, 1});
    graph4[2].push_back({3, 1});
    cout << "Test 4 (Expected 3): " << dijkstra(n, graph4, 0, 3) << endl;

    // Test 5: Larger graph with correct directions
    n = 6;
    vector<vector<pair<int, int>>> graph5(n);
    graph5[0].push_back({1, 7});
    graph5[0].push_back({2, 9});
    graph5[0].push_back({5, 14});
    graph5[1].push_back({2, 10});
    graph5[1].push_back({3, 15});
    graph5[2].push_back({3, 11});
    graph5[2].push_back({5, 2});
    graph5[5].push_back({4, 9});
    graph5[3].push_back({4, 6});
    cout << "Test 5 (Expected 20): " << dijkstra(n, graph5, 0, 4) << endl;

    return 0;
}
