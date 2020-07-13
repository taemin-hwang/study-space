#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
int fixed_seat[41];
vector<int> fs;
int cache[41][41];

int DP (int start, int end) {
    int &ret = cache[start][end];
    if(ret != -1) return ret;
    if(start >= end) return 1;

    ret = 0;

    if(fixed_seat[start] != 1 && fixed_seat[start+1] != 1) {
        ret += DP(start + 2, end);
        ret += DP(start + 1, end);
    } else {
        ret += DP(start + 2, end);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    cin >> m;

    memset(cache, -1, sizeof(cache));
    memset(fixed_seat, -1, sizeof(fixed_seat));
    fs.resize(m + 1);

    int idx;
    for(int i = 1 ; i <= m; ++i) {
        cin >> idx;
        fixed_seat[idx] = 1;
        fs[i] = idx;
    }

    int ret = 1;
    int start = 0, end = n;
    for(int i = 1 ; i <= m; ++i) {
        end = fs[i];
        ret *= DP(start+1, end);
        start = end;
    }
    ret *= DP(fs[m]+1, n);

    cout << ret << endl;
}
