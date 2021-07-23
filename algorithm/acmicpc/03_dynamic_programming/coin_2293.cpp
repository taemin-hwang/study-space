#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    int coin[101];
    int d[10001] = {0};

    for(int i = 0; i < n; ++i) {
        cin >> coin[i];
    }

    d[0] = 1;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1 j <= k; ++j) {
            if( j >= coints[i]) {
                d[j] += d[j-coins[i]];
            }
        }
    }

    cout << d[k] << endl;
}
