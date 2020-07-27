#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
int map[1000][1000];
int cache[1000][1000];
int INF = 123456789;

bool isOutOfRange(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m) return true;
    else return false;
}

int dp(int x, int y) {
    if(isOutOfRange(x, y)) return 0;
    if(map[x][y] == 0) return 0;

    int &ret = cache[x][y];
    if(ret != -1) return ret;

    ret = 1;
    int min_val = INF;

    min_val = min(min_val, dp(x+1, y));
    min_val = min(min_val, dp(x, y+1));
    min_val = min(min_val, dp(x+1, y+1));

    ret += min_val;
    return ret;
}


int sol() {
    int ret = -1;
    memset(cache, -1, sizeof(cache));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ret = max(ret, dp(i, j));
        }
    }

    //for(int i = 0; i < n; i++) {
    //    for(int j = 0; j < m; j++) {
    //        cout << cache[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    return ret*ret;
}

int main() {
    cin >> n >> m;
    std::vector<std::string> line;
    line.resize(n);

    for(int i = 0; i < n; i++) {
        cin >> line[i];;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(line[i][j] == '1') map[i][j] = 1;
            else map[i][j] = 0;
        }
    }

    cout << sol() << endl;
}
