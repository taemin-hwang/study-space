#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> adj;
vector<string> str;
int visit[101];

void MakeGraph() {
    for(int i = 0 ; i < n; i++) {
        int len = str[i].size();
        for(int j = 0 ; j < n; j++) {
            if(i == j) continue;
            if(str[i][len-1] == str[j][0]) {
                adj[i][j] = 1;
            } else {
                adj[i][j] = 0;
            }
        }
    }
}

vector<int> st;
int max_degree;
void dfs(int here, int degree) {
    if(visit[here]) return;

    visit[here] = 1;
    for(int i = 0 ; i < n; i++)
        adj[i][here] = 0;

    for(int there = 0; there < n; there++) {
        if(adj[here][there] > 0 && !visit[there]) {
            dfs(there, degree+1);
        }
    }

    max_degree = max(max_degree, degree);
    st.push_back(here);
}

int vertex[101];
bool dfsAll() {
    bool ret = false;

    for(int here = 0 ; here < n; here++) {
        memset(visit, 0, sizeof(visit));
        max_degree = 0;
        st.clear();
        dfs(here, 1);
        if(max_degree == n) {
            return true;
        }
    }
    return false;
}

int main() {
    int c;
    vector<vector<string>> ans;
    cin >> c;
    ans.resize(c);
    for(int i = 0 ; i < c; i++) {
        cin >> n;
        adj.resize(n);
        str.resize(n);
        for(int j = 0 ; j < n; j++) adj[j].resize(n);
        for(int j = 0 ; j < n; j++)cin >> str[j];

        MakeGraph();

        if(!dfsAll()) {
            ans[i].push_back("IMPOSSIBLE");
        } else {
            reverse(st.begin(), st.end());
            for(auto p : st) {
                ans[i].push_back(str[p]);
            }
        }

    }

    for(int i = 0 ; i < c; i++) {
        for(auto p : ans[i]) {
            cout << p << " ";
        }
        cout << endl;
    }


}
