#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int r, c;
int net[500][500][4];
int visit[500][500];
vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

bool isOutOfRange(int x, int y) {
    if(x < 0 || x >= r || y < 0 || y >= c) {
        return true;
    }
    return false;
}

int min_val = INT_MAX;
int depth = 0;
void dfs(int x, int y, int sum) {
    if(isOutOfRange(x, y)) return;
    if(visit[x][y] > 0) return;

    visit[x][y] = 1;
    depth++;

    cout << x+1 << ", " << y+1 << " : " << sum << "( " << depth << ")" << endl;

    if(depth == r*c) {
        if(min_val > sum) min_val = sum;
        return;
    }

    for(int i = 0; i < 4; i++) {
        dfs(x + dir[i].first, y + dir[i].second, sum + net[x][y][i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t, tmp;
    cin >> t;
    vector<int> ans;

    for(int i = 0; i < t; i++) {
        cin >> r >> c;

        for(int j = 0; j < r; j++) {
            for(int k = 0; k < c-1; k++) {
                cin >> tmp;
                net[j][k][1] = tmp;
                net[j][k+1][0] = tmp;
            }
        }

        for(int j = 0; j <r-1; j++) {
            for(int k = 0; k < c; k++) {
                cin >> tmp;
                net[j][k][3] = tmp;
                net[j+1][k][2] = tmp;
            }
        }

        depth = 0;
        min_val = INT_MAX;
        for(int x = 0; x < r; x++) {
            for(int y = 0; y < c; y++) {
                memset(visit, 0, sizeof(visit));
                dfs(x, y, 0);
            }
        }
        ans.push_back(min_val);
    }

    for(auto p : ans) {
        cout << p << endl;
    }
}
