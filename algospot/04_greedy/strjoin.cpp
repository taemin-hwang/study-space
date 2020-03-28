#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> str;
int cache[1001];
int strjoin() {
    int ret = 0;

    int min1 = (*str.begin()).first;
    if(str[min1] == 1) {
        str.erase(min1);
    } else {
        str[min1]--;
    }
    int min2 = (*str.begin()).first;
    if(str[min2] == 1) {
        str.erase(min2);
    } else {
        str[min2]--;
    }

    //cout << min1 << ", " << min2 << endl;
    if(str.size() == 0) return min1+min2;

    if(str.find(min1+min2) == str.end()) {
        str.insert({min1+min2, 1});
    } else {
        str[min1+min2]++;
    }
    ret += min1+min2+strjoin();

    return ret;
}

int main() {
    int c, n, t;
    vector<int> ans;
    cin >> c;
    ans.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> n;
        memset(cache, 0, sizeof(cache));
        for(int j = 0; j < n; j++) {
            cin >> t;
            if(cache[t] == 0) {
                str.insert({t, 1});
                cache[t]++;
            } else {
                str[t]++;
            }
        }

        ans[i] = strjoin();
    }

    for(int i = 0 ; i < c; i++) {
        cout << ans[i] << endl;
    }
}
