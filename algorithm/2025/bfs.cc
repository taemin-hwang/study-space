#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // moving directions

int bfs(vector<vector<int>>& grid) {
    // it is typical bfs problem for finding the shortest path
    // we can use a queue for traversing all the node

    if(grid[0][0] == 1 || grid.back().back() == 1) return -1;

    vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0));

    queue<pair<int, pair<int, int>>> mq;
    // initialize dist(1) , (0, 0) - left-top
    mq.push({1, {0, 0}});

    while(!mq.empty()){
        int qsize = mq.size();
        for(int i = 0 ; i < qsize; i++) {
            auto [dist, pos] = mq.front();
            mq.pop();
            auto [row, col] = pos;

            visited[row][col] = 1;

            if(row == grid.size() - 1 && col == grid[0].size() - 1) return dist;

            for(auto dir : dirs) {
                int new_r = row + dir.first;
                int new_c = col + dir.second;

                if(new_r < 0 || new_c < 0 || new_r >= grid.size() || new_c >= grid[0].size()) continue; // skip the out of range
                if(grid[new_r][new_c] == 1) continue; // skip the wall
                if(visited[new_r][new_c] == 1) continue; // skip the already visited cell

                mq.push({dist + 1, {new_r, new_c}});
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<int>> grid1 = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    cout << "Test 1 (Expected 5): " << bfs(grid1) << endl;

    vector<vector<int>> grid2 = {
        {0, 1},
        {1, 0}
    };
    cout << "Test 2 (Expected -1): " << bfs(grid2) << endl;

    vector<vector<int>> grid3 = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    cout << "Test 3 (Expected -1): " << bfs(grid3) << endl;
    vector<vector<int>> grid4 = {
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 1, 1, 0}
    };
    cout << "Test 4 (Expected 9): " << bfs(grid4) << endl;

    vector<vector<int>> grid5 = {
        {0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0}
    };
    cout << "Test 5 (Expected 11): " << bfs(grid5) << endl;

    return 0;
}
