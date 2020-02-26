#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxArea(const vector<int>& tc, int begin, int end) {
    int maxArea = 0;
    int left, mid, right;

    if(end <= begin) return tc[begin];

    left = getMaxArea(tc, begin, (begin + end)/2 );
    right = getMaxArea(tc, (begin + end)/2 + 1, end);
    
    int midleft, midright;
    int hileft, hiright;
    int minHeight;

    midleft = (begin + end)/2;
    midright = (begin + end)/2 + 1;
    minHeight = min(tc[midleft], tc[midright]);
    mid = 0;

    while(midleft >= begin && midright <= end) {
        mid = max(mid, minHeight * (midright - midleft + 1));
        
        if(midright+1 <= end) {
            hiright = tc[midright+1];
        } else {
            hiright = 0;
        }

        if(midleft-1 >= begin) {
            hileft = tc[midleft-1];
        } else {
            hileft = 0;
        }

        if(hiright > hileft) {
            midright++;
            minHeight = min(minHeight, tc[midright]);
        } else {
            midleft--;
            minHeight = min(minHeight, tc[midleft]);
        }
    }

    maxArea = max(maxArea, left);
    maxArea = max(maxArea, mid);
    maxArea = max(maxArea, right);

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
        cout << getMaxArea(tc[i], 0, tc[i].size()-1) << endl;
    }

}
