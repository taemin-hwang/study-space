#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int cache[101][101];
int getCount(int width, int n) {
    //int ret;
    int &ret = cache[width][n];
    if(ret != -1) return ret;
    if(n == 0) return ret = 1;

    ret = 0;
    for(int j = 1; j <= n; j++) {
        int tmp = (width + j - 1) * getCount(j, n - j);
        ret += tmp % 10000000;
    }

    return ret %= 10000000;
}

int getPoly(int tc) {
    int ret = 0;

    for(int i = 1 ; i <= tc; i++) {
        int tmp = getCount(i, tc-i);
        ret += tmp % 10000000;
    }

    return ret % 10000000;
}

int main() {
    int c;
    vector<int> tc;
    cin >> c;

    tc.resize(c);
    for(int i = 0 ; i < c; i++) {
        cin >> tc[i];
    }

    for(int i = 0 ; i < c; i++) {
        memset(cache, -1, sizeof(cache));
        cout << getPoly(tc[i]) << endl;
    }

}
