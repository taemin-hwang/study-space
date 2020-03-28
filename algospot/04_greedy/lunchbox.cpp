#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>

using namespace std;

vector<int> m, e;
multiset<pair<int,int>> lists;
int lunchbox(int start, int end) {
    if(lists.size() < 1) return end;

    int ret = 0;
    auto itr = lists.rbegin();
    int st = start + m[itr->second];
    int ed = max(end, start + m[itr->second] + e[itr->second]);
    lists.erase(*itr);

    ret = lunchbox(st, ed);

    return ret;
}

int main() {
    int c, n;
    vector<int> ans;
    cin >> c;
    ans.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> n;
        m.resize(n);
        e.resize(n);
        for(int j = 0; j < n; j++) {
            cin >> m[j];
        }
        for(int j = 0; j < n; j++) {
            cin >> e[j];
        }
        for(int j = 0; j < n; j++) {
            lists.insert({e[j], j});
        }
        ans[i] = lunchbox(0, 0);
    }

    for(int i = 0; i < c; i++) {
        cout << ans[i] << endl;
    }

}
