#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int getCost(vector<int>& tc) {
    if(tc.size() == 1) return 0;

    sort(tc.begin(), tc.end(), greater<int>());

    int v1 = tc.back();
    tc.pop_back();
    int v2 = tc.back();
    tc.pop_back();

    tc.push_back(v1 + v2);

    return v1 + v2 + getCost(tc);
}

int main() {
    int c, w;
    vector<vector<int> > tc;

    cin >> c;
    tc.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> w;
        tc[i].resize(w);
        for(int j = 0 ; j < w; j++) {
            cin >> tc[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        cout << getCost(tc[i]) << endl;
    }
}
