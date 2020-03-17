#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>

using namespace std;

bool set1(int x, int y, vector<string>& map) {
    if(map[x][y] != '.') return false;
    if(y+1 >= 5 || map[x][y+1] != '.') return false;
    map[x][y] = '#';
    map[x][y+1] = '#';
    return true;
}

bool set2(int x, int y, vector<string>& map) {
    if(map[x][y] != '.') return false;
    if(x+1 >= 5 || map[x+1][y] != '.') return false;
    map[x][y] = '#';
    map[x+1][y] = '#';
    return true;
}

bool set3(int x, int y, vector<string>& map) {
    if(map[x][y] != '.') return false;
    if(y+1 >= 5 || map[x][y+1] != '.') return false;
    if(x+1 >= 5 || map[x+1][y+1] != '.') return false;
    map[x][y] = '#';
    map[x][y+1] = '#';
    map[x+1][y+1] = '#';
    return true;
}

bool set4(int x, int y, vector<string>& map) {
    if(map[x][y] != '.') return false;
    if(x+1 >= 5 || map[x+1][y] != '.') return false;
    if(y+1 >= 5 || map[x+1][y+1] != '.') return false;
    map[x][y] = '#';
    map[x+1][y] = '#';
    map[x+1][y+1] = '#';
    return true;
}

int cache[1<<26];

int getidx(const vector<string> map) {
    int ret = 1;
    for(int i = 0 ; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            ret = ret << 1;
            if(map[i][j] == '#') ret++;
        }
    }
    return ret;
}

bool blockgame(vector<string> map) {
    //cout << endl;
    //for(int i = 0 ; i < 5; i++) {
    //    for(int j = 0 ; j < 5; j++) {
    //        cout << map[i][j];
    //    }
    //    cout << endl;
    //}
    //getchar();
    int& ret = cache[getidx(map)];
    if(ret != -1) return ret;
    ret = 0;
    int cnt = 0;
    int fin = 0;
    vector<string> tmp = map;
    for(int i = 0 ; i < 5; i++) {
        for(int j = 0 ; j < 5; j++) {
            tmp = map;
            if(set1(i, j, tmp)) {
                if(!blockgame(tmp)) cnt++;
                fin++;
            }
            tmp = map;
            if(set2(i, j, tmp)) {
                if(!blockgame(tmp)) cnt++;
                fin++;
            }
            tmp = map;
            if(set3(i, j, tmp)) {
                if(!blockgame(tmp)) cnt++;
                fin++;
            }
            tmp = map;
            if(set4(i, j, tmp)) {
                if(!blockgame(tmp)) cnt++;
                fin++;
            }
        }
    }
    if(fin == 0) return ret = 0;
    if(cnt > 0) return ret = 1;

    return ret;
}

int main() {
    int c;
    vector<string> map;
    vector<bool> ans;

    map.resize(5);

    cin >> c;
    for(int i = 0 ; i < c; i++) {
        for(int j = 0 ; j < 5; j++) {
            cin >> map[j];
        }
        memset(cache, -1, sizeof(cache));
        ans.push_back(blockgame(map));
    }

    for(int i = 0 ; i < c; i++) {
        if(ans[i]) cout << "WINNING" << endl;
        else cout << "LOSING" << endl;
    }
}
