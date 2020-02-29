#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int cache[100][100];
int n;
int getMaxPath(const vector<vector<int>>& tc, int x, int y) {
    if(x == n-1) return tc[x][y];
    int &ret = cache[x][y];

    if(ret != -1) return tc[x][y];
    ret = max(getMaxPath(tc, x+1, y), getMaxPath(tc, x+1, y+1)) + tc[x][y];
    return ret;
}

int main() {
    int c;
    cin >> c;
    vector<vector<vector<int>>> tc;

    tc.resize(c);
    for(int i = 0 ; i < c ; i++) {
        cin >> n;
        tc[i].resize(n);
        for(int j = 0; j < n ; j++) {
            tc[i][j].resize(j+1);
            for(int k = 0 ; k < j+1; k++) {
                cin >> tc[i][j][k];
            }
        }
    }

    for(int i = 0 ; i < c; i++) {
        memset(cache, -1, sizeof(cache));
        n = tc[i].size();
        cout << getMaxPath(tc[i], 0, 0) << endl;
    }
}
