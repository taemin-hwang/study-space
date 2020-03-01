#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;


int cache[1001][1001][11];
vector<vector<int>> tc;

int getDevian(int begin, int end, int num, int idx) {
    int sum = 0;
    for(int i = begin; i <= end; i++) {
        sum += pow(tc[idx][i] - num, 2);
    }
    return sum;
}

int getMinDevian(int begin, int end, int idx) {
    int ret = INT_MAX;
    for(int i = 1 ; i <= tc[idx][end] ; i++) {
        ret = min(ret, getDevian(begin, end, i, idx));
    }
    return ret;
}

int quantize(int begin, int end, int qt, int idx) {
    int &ret = cache[begin][end][qt];
    if(ret != -1) return ret;

    ret = INT_MAX;
    if(qt == 1) {
        ret = getMinDevian(begin, end, idx);
        return ret;
    }

    for(int i = begin; i <= end - qt + 1; i++) {
        //if(tc[idx][i] > tc[idx][begin])
            ret = min(ret, getMinDevian(begin, i, idx) + quantize(i+1, end, qt-1, idx));
    }

    return ret;
}

int main() {
    int c, sz, n;
    vector<int> qt;

    cin >> c;
    tc.resize(c);
    qt.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> sz >> qt[i];
        tc[i].resize(sz);
        for(int j = 0 ; j < sz; j++) {
            cin >> tc[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        memset(cache, -1, sizeof(cache));
        sort(tc[i].begin(), tc[i].end());
        cout << quantize(0, tc[i].size()-1, qt[i], i) << endl;
    }
}
