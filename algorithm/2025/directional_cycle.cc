#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class DirectedCycleDetector {
 public:
    DirectedCycleDetector() = default;
    virtual ~DirectedCycleDetector() = default;

/*
    Problem Description
      - 0 -> 1, 1 -> 2, 2 -> 3 (false)
      - 0 -> 1, 1 -> 2, 2 -> 0 : has a cycle (true)

    Approach
      - Move all kinds of the path with backtracking
      - Find if there's cycle or not (3 visit state: unvisitied, visiting, visited)
      - backtracking could be implemented with recursive function
*/

    bool hasCycle(int start, int n, unordered_map<int, vector<int>>& mp, vector<int>& visited) {

        visited[start] = 1; // visiting

        auto children = mp[start];
        // loop over the children

        for(auto child : children) {
            if(visited[child] == 2) continue; // skip the visited cell
            if(visited[child] == 1) return true; // found a cycle, back edge -> cycle
            if(hasCycle(child, n, mp, visited)) return true; // if theres sub-cycle, return true
        }

        visited[start] = 2; // visited

        return false; // if traversing is done, return false
    }

    bool detectCycle(int n, vector<vector<int>>& edges) {
        vector<int> visited(n, 0); // visit state

        // make a graph from the edge
        unordered_map<int, vector<int>> mp; // from -> [to1, to2, ...]
        for(auto e : edges) {
            int from = e[0];
            int to = e[1];
            mp[from].push_back(to);
        }

        // assign start node over the loop
        for(int i = 0 ; i < n; i++) {
            visited = vector<int>(n, 0); // reset visited cell
            if(hasCycle(i, n, mp, visited)) return true;
        }
        return false;
    }
};


int main() {
    DirectedCycleDetector detector;

    vector<tuple<int, vector<vector<int>>, bool>> testcases = {
        {4, {{0,1},{1,2},{2,3}}, false},
        {3, {{0,1},{1,2},{2,0}}, true},
        {4, {{0,1},{1,2},{2,3},{3,1}}, true},
        {5, {{0,1},{2,3}}, false},
        {4, {}, false}
    };

    int idx = 1;
    for (auto& [n, edges, expected] : testcases) {
        bool result = detector.detectCycle(n, edges);
        cout << "Test Case " << idx++ << ": "
             << (result == expected ? "✅ Pass" : "❌ Fail") << endl;
    }

    return 0;
}
