#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;

int step[301];
int score[301][3];

int dp(int nth, int cnt) {
    if(nth <= 0) return 0;
    int& ret = score[nth][cnt];
    if(ret != -1) return ret;

    ret = step[nth];
    if(cnt >= 2) {
        ret += dp(nth - 2, 1);
    } else {
        ret += max(dp(nth - 1, cnt + 1), dp(nth - 2, 1));
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for(int i = 1; i <=n; ++i) {
        cin >> step[i];
    }

    memset(score, -1, sizeof(score));
    cout << dp(n, 1) << endl;
}
