#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

int r, c;
int adj[101][101];
int dist[101][101];

bool isOutOfRange(int y, int x) {
    if(x <= 0 || x > r || y <= 0 || y > c)
        return true;
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    queue<pair<int, int>> q;
    pair<int, int> start;
    cin >> c >> r;

    string s;
    for(int x = 1; x <= r; ++x) {
        cin >> s;
        for(int y = 1; y <= c; ++y) {
            adj[y][x] = s[y-1]-'0';
        }
    }

    cin >> start.first >> start.second;

    memset(dist, -1, sizeof(dist));
    dist[start.first][start.second] = 0;
    q.push(start);

    while(!q.empty()) {
        pair<int, int> here = q.front();
        q.pop();

        //TODO
        if(!isOutOfRange(here.first-1, here.second)) {
            if(adj[here.first-1][here.second] == 1) {
                if(dist[here.first-1][here.second] == -1) {
                    q.push({here.first-1, here.second});
                    dist[here.first-1][here.second] = dist[here.first][here.second] + 1;
                }
            }
        }
        if(!isOutOfRange(here.first+1, here.second)) {
            if(adj[here.first+1][here.second] == 1) {
                if(dist[here.first+1][here.second] == -1) {
                    q.push({here.first+1, here.second});
                    dist[here.first+1][here.second] = dist[here.first][here.second] + 1;
                }
            }
        }
        if(!isOutOfRange(here.first, here.second-1)) {
            if(adj[here.first][here.second-1] == 1) {
                if(dist[here.first][here.second-1] == -1) {
                    q.push({here.first, here.second-1});
                    dist[here.first][here.second-1] = dist[here.first][here.second] + 1;
                }
            }
        }
        if(!isOutOfRange(here.first, here.second+1)) {
            if(adj[here.first][here.second+1] == 1) {
                if(dist[here.first][here.second+1] == -1) {
                    q.push({here.first, here.second+1});
                    dist[here.first][here.second+1] = dist[here.first][here.second] + 1;
                }
            }
        }
    }

    int max_dist = INT_MIN;
    int remain_zergling = 0;
    for(int x = 1; x <= r; ++x) {
        for(int y = 1; y <= c; ++y) {
            if(adj[y][x] == 1 && dist[y][x] == -1) {
                remain_zergling++;
            }
            max_dist = max(max_dist, dist[y][x]);
        }
    }

    cout << max_dist + 3 << endl;
    cout << remain_zergling << endl;

}
