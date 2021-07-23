#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

int N, T[17], P[17];

const int NINF = -123456789;
int cache[17];

int DP(int start) {
    int& ret = cache[start];
    //cout << ret << ", " << start << endl;
    if(ret != -1) return ret;
    if(start > N) return 0;
    ret = NINF;

    ret = max(ret, DP(start+1));
    if(start + T[start] <= N + 1) {
        ret = max(ret, DP(start+T[start]) + P[start]);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> T[i] >> P[i];
    }

    memset(cache, -1, sizeof(cache));
    cout << DP(1) << endl;
}
