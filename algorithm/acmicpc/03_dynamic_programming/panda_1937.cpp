#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
int forest[500][500];
int cache[500][500];

bool isOutOfRange(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= n) return true;
    else return false;
}

int dp(int x, int y) {
    if(isOutOfRange(x, y)) return 0;

    int &ret = cache[x][y];
    if(ret != -1) return ret + 1;

    ret = 0;

    if(forest[x][y] < forest[x-1][y])
        ret = max(ret, dp(x-1, y));

    if(forest[x][y] < forest[x+1][y])
        ret = max(ret, dp(x+1, y));

    if(forest[x][y] < forest[x][y-1])
        ret = max(ret, dp(x, y-1));

    if(forest[x][y] < forest[x][y+1])
        ret = max(ret, dp(x, y+1));

    return ret + 1;
}

int sol() {
    int ret = -1;

    memset(cache, -1, sizeof(cache));
    for(int i = 0; i < n ; i++) {
        for(int j = 0; j < n; j++) {
            ret = max(ret, dp(i, j));
        }
    }

    //cout << endl;
    //for(int i = 0; i < n ; i++) {
    //    for(int j = 0; j < n; j++) {
    //        cout << cache[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> forest[i][j];
        }
    }

    cout << sol() << endl;
}
