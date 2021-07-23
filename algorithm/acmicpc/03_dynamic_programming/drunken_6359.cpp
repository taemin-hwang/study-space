#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

int room[101];
int n;
int dp(int k) {
    for(int i = 1; i <= n; ++i) {
        if(i % k == 0) {
            if(room[i] == -1) {
                room[i] = 1;
            } else {
                room[i] = -1;
            }
        }
    }

    if(n == k) {
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            if(room[i] == 1) {
                cnt++;
            }
        }
        return cnt;
    }


    return dp(k+1);
}

int main() {
    vector<int> ans;
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> n;
        memset(room, -1, sizeof(room));
        ans.push_back(dp(1));
    }

    for(auto p : ans) {
        cout << p << endl;
    }
}
