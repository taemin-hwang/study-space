#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;

int n, m;
int map[101][101];  //y, x

bool isOutOfRange(int y, int x) {
    if(y <=0 || y > n || x <= 0 || x > m) {
        return true;
    }
    return false;
}

int bfs(pair<int, int> src, pair<int, int> dst) {
    int shortest_path;

    int dist[101][101];
    dist[src.first][src.second] = 0;
    queue<pair<pair<int ,int>, int>> q;
    q.push({src, 0});

    vector<pair<int, int>> diff = {{-1, -2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    while(!q.empty()) {
        pair<int, int> here = q.front().first;
        int path = q.front().second;
        q.pop();

        for(int i = 0 ; i < diff.size() ; i++) {
            int y = here.first + diff[i].first;
            int x = here.second + diff[i].second;
            //cout << y << ", " << x << endl;
            if(!isOutOfRange(y, x)) {
                if(dist[y][x] == 0) {
                    dist[y][x] = path + 1;
                    q.push({{y, x}, path+1});
                }
            }
        }
    }


    shortest_path = dist[dst.first][dst.second];

    return shortest_path;
}

int main() {
    cin >> n >> m;

    pair<int ,int> src, dst;
    cin >> src.first >> src.second;
    cin >> dst.first >> dst.second;

    cout << bfs(src, dst) << endl;
}
