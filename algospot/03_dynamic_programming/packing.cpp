#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n, w;
vector<pair<string, pair<int, int>>> tc;
int path[101];
int cache[101];
int getMaxLevel(int pos, int w) {
    int& ret = cache[pos];
    if(ret != 0) return 0;
    if(w < 0) return 0;

    ret = tc[pos].second.second;
    int maxRet = ret, maxIdx = pos;
    for(int i = 1; i <= n; i++) {
        if(cache[i] != 0) {
            continue;
        }
        int tmp = ret + getMaxLevel(i, w - tc[i].second.first);
        if(maxRet < tmp) {
            maxIdx = i;
            maxRet = tmp;
        }
        cache[i] = 0;
    }
    path[pos+1] = maxIdx;
    return ret = maxRet;
}

int main() {
    int c, capacity, level;
    string item;
    vector<int> ns, ws;
    vector<vector<pair<string, pair<int, int>>>> tcs;

    cin >> c;
    tcs.resize(c);
    ns.resize(c);
    ws.resize(c);
    for(int i = 0 ; i < c; i++) {
        cin >> ns[i] >> ws[i];
        tcs[i].resize(ns[i]+1);
        for(int j = 1; j <= ns[i]; j++) {
            cin >> item >> capacity >> level;
            tcs[i][j] = {item, {capacity, level}};
        }
    }
    for(int i = 0; i < c; i++) {
        tc = tcs[i];
        n = ns[i];
        w = ws[i];
        memset(cache, 0, sizeof(cache));
        cout << getMaxLevel(0, w) << endl;
        for(int i = 0; i <= 101; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}
