#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int cache[100][100];
int maxPath = 0;
int getMaxPath(const vector<vector<int>>& tc, int x, int y, int sum) {
    if(x >= tc.size()) return sum;
    int &ret = cache[x][y];

    if(ret == -1 || ret < sum + tc[x][y]) ret = sum + tc[x][y];
    else return ret;

    ret = max(getMaxPath(tc, x+1, y, sum+tc[x][y]), getMaxPath(tc, x+1, y+1, sum+tc[x][y]));
    if(maxPath < ret) maxPath = ret;
    return ret;
}

int main() {
    int c, n;
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
        maxPath = 0;
        cout << getMaxPath(tc[i], 0, 0, 0) << endl;
    }
}
