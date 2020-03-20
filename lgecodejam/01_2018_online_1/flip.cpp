#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
vector<int> lists;
int flip(int cmd, int k) {
    int idx;
    double didx;
    if(cmd == 0 || cmd == n) return k;
    if(cmd > 0) {
        if(cmd % 2 == 0) {
            if(cmd < k) return k;
            didx = (cmd+1)/2;
            if(didx > k) {
                idx = didx+1;
            } else {
                idx = didx;
            }
            k = idx;
        } else {
            if(cmd < k) return k;
            idx = (cmd+1)/2;
            k = 2 * idx - k;
        }
    } else {
        if(cmd % 2 == 0) {
            if(n + cmd > k) return k;
            didx = (n + cmd + n + 1)/2;
            if(didx > k) {
                idx = didx+1;
            } else {
                idx = didx;
            }
        } else {
            if(n + cmd > k) return k;
            idx = (n + cmd + n + 1)/2;
            k = 2 * idx - k;
        }
    }

    return k;
}

int main() {
    int k, cmd;
    cin >> n >> k >> m;
    lists.resize(n);
    for(int i = 0 ; i < n; i++) {
        cin >> lists[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> cmd;
        k = flip(cmd, k);
        cout << k << endl;
    }

    cout << k << endl;
}
