#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int m, n;
bool WHITE = true, BLACK = false;
bool map[50][50];
int cache[50][50];


bool isOutOfRange(const int& init_x, const int& init_y, int x, int y) {
    if(y < 0 || y >= m || x < 0 || x >= n) return true;
    else if(x - init_x >= 8 || y - init_y >= 8) return true;
    else return false;
}

int sol(const int& init_x, const int& init_y, int x, int y, bool color) {
    if(isOutOfRange(init_x, init_y, x, y)) return 0;
    int & ret = cache[x][y];
    if(ret != -1) return 0;

    ret = 0;

    if(map[x][y] != color) {
        ret++;
    }
    ret += sol(init_x, init_y, x+1, y, !color);
    ret += sol(init_x, init_y, x, y+1, !color);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    string s;
    char c;

    for(int y = 0; y < m; ++y) {
        cin >> s;
        for(int x = 0; x < n; ++x) {
            if(s[x] == 'W') {
                map[x][y] = WHITE;
            } else {
                map[x][y] = BLACK;
            }
        }
    }

    int ans = INT_MAX;
    for(int y = 0; y <= m - 8; ++y) {
        for(int x = 0; x <= n - 8; ++x) {
            memset(cache, -1, sizeof(cache));
            ans = min(ans, sol(x, y, x, y, WHITE));
            memset(cache, -1, sizeof(cache));
            ans = min(ans, sol(x, y, x, y, BLACK));
        }
    }
    cout << ans << endl;

}
