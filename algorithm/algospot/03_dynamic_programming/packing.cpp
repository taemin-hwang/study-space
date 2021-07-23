#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n, w;
vector<pair<string, pair<int, int>>> tc;
int cache[101][1001];
int getMaxLevel(int pos, int w) {
    if(pos == n) return 0;
    int& ret = cache[pos][w];
    if(ret != -1) return ret;

    ret = getMaxLevel(pos+1, w);
    if(w >= tc[pos].second.first)
        ret = max(ret, getMaxLevel(pos+1, w - tc[pos].second.first) + tc[pos].second.second);

    return ret;
}

void reconstruct(int pos, int w, vector<string>& ans) {
    if(pos == n) return;
    if(getMaxLevel(pos+1, w) == getMaxLevel(pos, w)) {
        reconstruct(pos+1, w, ans);
    } else {
        ans.push_back(tc[pos].first);
        reconstruct(pos+1, w-tc[pos].second.first, ans);
    }
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
        vector<string> ans;
        memset(cache, -1, sizeof(cache));
        cout << getMaxLevel(0, w);
        reconstruct(0, w, ans);
        cout << " " <<  ans.size() << endl;
        for(auto p : ans) {
            cout << p << endl;
        }
    }
}
