#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int n, m;
string ans;
vector<string> map;

int cache[101][101][101][9];

bool isOutOfRange(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m) return true;
    return false;
}

int word_search(int x, int y, int idx, int dir) {
    int &ret = cache[x][y][idx][dir];
    if(isOutOfRange(x, y)) return 0;
    if(idx == ans.size()-1 && ans[idx] == map[x][y]) return 1;
    if(ans[idx] != map[x][y]) return 0;
    if(ret != -1) return ret;

    ret = 0;

    if(dir == 0) {
        ret = max(ret, word_search(x-1, y-1, idx+1, 1));
        ret = max(ret, word_search(x-1, y  , idx+1, 2));
        ret = max(ret, word_search(x-1, y+1, idx+1, 3));
        ret = max(ret, word_search(x  , y-1, idx+1, 4));
        ret = max(ret, word_search(x  , y+1, idx+1, 5));
        ret = max(ret, word_search(x+1, y-1, idx+1, 6));
        ret = max(ret, word_search(x+1, y  , idx+1, 7));
        ret = max(ret, word_search(x+1, y+1, idx+1, 8));
    } else {
        switch(dir) {
            case 1: ret = max(ret, word_search(x-1, y-1, idx+1, 1)); break;
            case 2: ret = max(ret, word_search(x-1, y  , idx+1, 2)); break;
            case 3: ret = max(ret, word_search(x-1, y+1, idx+1, 3)); break;
            case 4: ret = max(ret, word_search(x  , y-1, idx+1, 4)); break;
            case 5: ret = max(ret, word_search(x  , y+1, idx+1, 5)); break;
            case 6: ret = max(ret, word_search(x+1, y-1, idx+1, 6)); break;
            case 7: ret = max(ret, word_search(x+1, y  , idx+1, 7)); break;
            case 8: ret = max(ret, word_search(x+1, y+1, idx+1, 8)); break;
        }
    }

    return ret;
}


int main() {
    int ret = 0;
    cin >> ans;
    cin >> n >> m;
    map.resize(n);
    for(int i = 0 ; i < n; i++) {
        cin >> map[i];
    }

    memset(cache, -1, sizeof(cache));
    for(int i = 0 ; i < n; i++) {
        for(int j = 0 ; j < m; j++) {
            if(ans[0] == map[i][j]) {
                if(word_search(i, j, 0, 0)) {
                    ret = 1;
                    break;
                }
            }
        }
    }

    cout << ret << endl;
}
