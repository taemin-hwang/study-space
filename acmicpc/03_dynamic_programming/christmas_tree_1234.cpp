#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n, r, g, b;
int cache[11][101][101][101];
int fact[11];

int sol(int level, int red, int green, int blue) {
    if(red < 0 || green < 0 || blue < 0) return 0;
    if(level > n) return 1;

    int &ret = cache[level][red][green][blue];
    if(ret != -1) return ret;
    ret = 0;

    if(red >= level) {
        ret += sol(level+1, red-level, green, blue);
    }

    if(green >= level) {
        ret += sol(level+1, red, green-level, blue);
    }

    if(blue >= level) {
        ret += sol(level+1, red, green, blue-level);
    }

    if(level % 3 == 0) {
        int diff = level/3;
        ret += (fact[level] / 6) * sol(level+2, red-diff, green-diff, blue-diff);
    }
    if(level % 2 == 0) {
        int diff = level/2;
        ret += (fact[level] / 2) * sol(level+1, red-diff, green-diff, blue);
        ret += (fact[level] / 2) * sol(level+1, red-diff, green, blue-diff);
        ret += (fact[level] / 2) * sol(level+1, red, green-diff, blue-diff);
    }

    return ret;
}

int factorial(int n) {
    int &ret = fact[n];
    if(ret != -1) return ret;
    if(n == 1) return ret = 1;
    return ret = factorial(n-1) * n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> r >> g >> b;

    memset(fact, -1, sizeof(fact));
    memset(cache, -1, sizeof(cache));

    cout << sol(1, r, g, b) << endl;
}
