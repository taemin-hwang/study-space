#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int visit[1001];
int exclude[1001];
int adj[1001][1001];
int w[1001], q[1001];
int n;

long long dfs(int here) {
    if(visit[here] > 0) return 0;
    if(exclude[here] > 0) return 0;

    long long ret = 0;

    visit[here] = 1;
    for(int i = 1; i <= n; i++) {
        if(adj[here][i] == 1)
            exclude[i] = 1;
    }

    for(int there = 1; there <= n; there++) {
        if(here != there && adj[here][there] == 0) {
            ret = max(ret, dfs(there));
        }
    }

    for(int i = 1; i <= n; i++) {
        if(adj[here][i] == 1)
            exclude[i] = 0;
    }

    return ret + w[here];

}

long long dfsAll() {
    long long ret = 0;

    memset(visit, 0, sizeof(visit));
    memset(exclude, 0, sizeof(exclude));

    for(int here = 1; here <= n; here++) {
        ret = max(ret, dfs(here));
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c;
    vector<long long> ans;
    cin >> c;

    for(int i = 0; i < c; i++) {
        cin >> n;
        memset(adj, 0, sizeof(adj));

        for(int j = 1; j <= n; j++) {
            cin >> w[j] >> q[j];

            adj[j][q[j]] = 1;
            adj[q[j]][j] = 1;
        }

        ans.push_back(dfsAll());
    }

    for(auto p : ans) {
        cout << p << endl;
    }


}
