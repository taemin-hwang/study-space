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
    if(cmd > 0) {
        if(k <= cmd) {
            if(cmd % 2 != 0) {
                idx = (cmd+1)/2;
                k = idx - k + idx;
            } else {
                didx = (cmd+1.0)/2.0;
                if(didx > k) {
                    idx = (cmd+2)/2;
                    k = idx - k + idx -1;
                } else {
                    idx = (cmd)/2;
                    k = idx - k + idx +1;
                }
            }
        } else {
            return k;
        }
    } else {
        if(k > n + cmd) {
            if(cmd % 2 != 0) {
                idx = n + cmd + (1-cmd)/2;
                k = idx - k + idx;
            } else {
                didx = n + cmd + (1.0-cmd)/2.0;
                if(didx > k) {
                    idx = n + cmd +(2-cmd)/2;
                    k = idx - k +idx -1;
                } else {
                    idx = n + cmd +(0-cmd)/2;
                    k = idx - k +idx +1;
                }
            }
        } else {
            return k;
        }
    }

    return k;
}

int main() {
    int k, cmd;
    cin >> n >> k >> m;
    lists.resize(n);
    vector<int> cmds;
    for(int i = 0 ; i < n; i++) {
        cin >> lists[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> cmd;
        cmds.push_back(cmd);
    }

    for(int i = 0 ; i < m; i++) {
        k = flip(cmds[i], k);
    }

    cout << k << endl;
}
