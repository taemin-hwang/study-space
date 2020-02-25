#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxArea(vector<int> tc) {
    int tmpArea = 0;
    int maxArea = -1;
    int minHeight = 0;

    for(int i = 0; i < tc.size(); i++) {
        minHeight = tc[i];
        for(int j = i; j < tc.size(); j++) {
            minHeight = min(minHeight, tc[j]);
            tmpArea = (j-i+1) * minHeight;

            if(maxArea < 0 || maxArea < tmpArea) {
                maxArea = tmpArea;
            }
        }
    }

    return maxArea;
}

int main() {
    vector<vector<int> > tc;
    int c, sz;

    cin >> c;
    tc.resize(c);
    for(int i = 0; i < c; i++) {
        cin >> sz;
        tc[i].resize(sz);
        for(int j = 0; j < sz; j++) {
            cin >> tc[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        cout << getMaxArea(tc[i]) << endl;
    }

}
