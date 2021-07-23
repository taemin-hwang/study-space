#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n, m, s;
const int NINF = -123456789;
vector<int> vol_diff;
int cache[101][1001];

bool isOutOfRange(const int& vol) {
    if(vol < 0 || vol > m) return true;
    else return false;
}

int sol(int order, int curr_vol) {
    //cout << order << ", " << curr_vol << endl;
    if(isOutOfRange(curr_vol)) return -1;
    if(order >= n) return curr_vol;

    int &ret = cache[order][curr_vol];
    if(ret != NINF) return ret;

    ret = max(ret, sol(order+1, curr_vol + vol_diff[order]));
    ret = max(ret, sol(order+1, curr_vol - vol_diff[order]));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n >> s >> m;
    vol_diff.resize(n);

    for(int i = 0; i < n; i++) {
        cin >> vol_diff[i];
    }

    for(int i = 0; i < 101; i++) {
        for(int j = 0; j < 1001; j++) {
            cache[i][j] = NINF;
        }
    }

    cout << sol(0, s) << endl;
}
