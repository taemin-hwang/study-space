#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
int tri[501][501];
int cache[501][501];
const int NINF = -123456789;

int DP(int x, int y) {
    int& ret = cache[x][y];
    if(x > n) return 0;
    if(ret != -1) return ret;

    ret = NINF;

    ret = max(ret, DP(x+1, y) + tri[x][y]);
    ret = max(ret, DP(x+1, y+1) + tri[x][y]);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            cin >> tri[i][j];
        }
    }
    memset(cache, -1, sizeof(cache));
    cout << DP(1, 1) << endl;
}
