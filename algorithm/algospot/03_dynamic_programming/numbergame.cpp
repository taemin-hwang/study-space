#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

int n;
int tc[51];
int cache[51][51][2];
int numbergame(int start, int end, bool isH) {
    int &ret = cache[start][end][isH];
    if(ret != -1) return ret;
    if(start > end) {
        return 0;
    }

    if(start == end) {
        if(isH) {
            return tc[start];
        } else {
            return -tc[start];
        }
    }

    if(isH) {
        ret = INT_MIN;
        ret = max(ret, tc[start] + numbergame(start+1, end, !isH));
        ret = max(ret, tc[end]   + numbergame(start, end-1, !isH));
        if(end - start >= 1) {
            ret = max(ret, numbergame(start+2, end, !isH));
            ret = max(ret, numbergame(start, end-2, !isH));
        }
    } else {
        ret = INT_MAX;
        ret = min(ret, -tc[start] + numbergame(start+1, end, !isH));
        ret = min(ret, -tc[end]   + numbergame(start, end-1, !isH));
        if(end - start >= 1) {
            ret = min(ret, numbergame(start+2, end, !isH));
            ret = min(ret, numbergame(start, end-2, !isH));
        }
    }

    return ret;
}

int main() {
    int c;
    vector<int> ans;
    cin >> c;
    for(int i = 0 ; i < c; i++) {
        cin >> n;
        for(int j = 0; j < n; j++) {
            cin >> tc[j];
        }
        memset(cache, -1, sizeof(cache));
        ans.push_back(numbergame(0, n-1, true));
    }

    for(int i = 0; i < c; i++) {
        cout << ans[i] << endl;
    }
}
