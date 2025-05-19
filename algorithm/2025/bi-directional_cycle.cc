#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
 public:
    Solution() = default;
    virtual ~Solution() = default;


    /*
        0 -> 1, 1 -> 0

        Problem Description
         - Find the cycle in this graph
         - Check if there's disconnection in this graph
         - Return true if it is tree, or return false

        Approach
         - make a graph from the edges
         - find a cycle with backtracking with 3 state (unvisited = 0, visiting = 1, visited = 2)
    */

    bool hasCycle(int start, int from, int n, unordered_map<int, vector<int>>&mp, vector<int>& visit) {

        visit[start] = 1; // visiting

        auto tos = mp[start];

        // loop over the next nodes
        for(auto to : tos) {
            if(to == from) continue; // skip the parent cell (bi-directional graph)
            if(visit[to] != 0) return true; // found a cycle
            if(visit[to] == 0) {
                if(hasCycle(to, start, n, mp, visit)) return true;
            }
        }

        return false;
    }

    bool isDisconnected(vector<int>& visit) {
        for(auto v : visit) {
            if(v == 0) return true;
        }
        return false;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        // a graph from edges
        unordered_map<int, vector<int>> mp; // key, value (from -> [to1, to2, ...])
        for(auto e : edges) {
            int from = e[0];
            int to = e[1];
            mp[from].push_back(to);
            mp[to].push_back(from);
        }

        // a list for checking visit
        vector<int> visit(n, 0);

        bool has_cycle = false;
        if(has_cycle = hasCycle(0, -1, n, mp, visit)) {
            cout << "Found a cycle" << endl;
            return false;
        }

        bool is_disconnected = false;
        if(isDisconnected(visit)) {
            cout << "Found a disconnection" << endl;
            return false;
        }

        return true;
    }
};


int main() {
    Solution sol;
    vector<tuple<int, vector<vector<int>>, bool>> testcases = {
        {5, {{0,1},{0,2},{0,3},{1,4}}, true},
        {5, {{0,1},{1,2},{2,0},{3,4}}, false},
        {4, {{0,1},{2,3}}, false},
        {4, {{0,1},{1,2},{2,3},{1,3}}, false},
        {1, {}, true}
    };

    int idx = 1;
    for (auto& [n, edges, expected] : testcases) {
        bool result = sol.validTree(n, edges);
        cout << "Test Case " << idx++ << ": " << (result == expected ? "✅ Pass" : "❌ Fail") << endl;
    }
    return 0;
}
