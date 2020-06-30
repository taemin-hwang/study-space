#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <set>

using namespace std;

int n;

set<vector<int>> cache;
long long dp(vector<int> x) {
    sort(x.begin(), x.end());
    if(cache.find(x) != cache.end()) return 0;
    cache.insert(x);

    vector<int> tmp = x;
    long long ret = 1;
    for(int i = 0; i < x.size(); ++i) {
        tmp = x;
        if(x[i] > 1) {
            --tmp[i];
            ret += dp(tmp);
        }
    }

    return ret % 1000000007;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<long long> ans;
    int t;
    string tmp;
    vector<int> x;
    cin >> t;
    ans.reserve(t);
    for(int i = 0; i < t; ++i) {
        cin >> n;
        x.clear();
        x.resize(n);
        for(int j = 0; j < n; ++j) {
            cin >> x[j];
        }
        cache.clear();
        ans.push_back((n * dp(x)) % 1000000007);
    }

    for(auto p : ans) {
        cout << p << endl;
    }
}
