#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

int n, m;
int visit[1001];
int adj[1001][1001];

// tree visiting every vertex

int ST(int here) {
    if(visit[here] != -1) return 0;
    visit[here] = 1;

    int ret = 1;

    for(int i = 1 ; i <= n; ++i) {
        if(adj[here][i] == 1) {
            ret += ST(i);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t, here, there;
    vector<int> ans;

    cin >> t;

    for(int i = 0 ; i < t; ++i) {
        cin >> n >> m;

        memset(adj, -1, sizeof(adj));
        memset(visit, -1, sizeof(visit));

        for(int j = 0; j < m; ++j) {
            cin >> here >> there;
            adj[here][there] = 1;
            adj[there][here] = 1;
        }
        ans.push_back(ST(1));
    }

    for(auto p : ans) {
        cout << p-1 << endl;
    }
}
