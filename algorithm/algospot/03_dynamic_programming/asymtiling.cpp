#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

int cache1[101];
int cache2[101];
int CountAllTiles(int width) {
    int& ret = cache1[width];
    if(ret != -1) return ret;
    if(width < 0) return ret = 0;
    if(width == 0) return ret = 1;

    ret = CountAllTiles(width-1) + CountAllTiles(width-2);
    ret %= 1000000007;
    return ret;
}

int CountSymTiles(int width) {
    int& ret = cache2[width];
    if(ret != -1) return ret;
    if(width < 0) return ret = 0;
    if(width == 0 || width == 1) return ret = 1;
    if(width == 2) return ret = 2;

    ret = CountSymTiles(width-2) + CountSymTiles(width-4);
    ret %= 1000000007;
    return ret;
}

int main() {
    int c;
    vector<int> tc;
    cin >> c;
    tc.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> tc[i];
    }

    for(int i = 0 ; i < c; i++) {
        memset(cache1, -1, sizeof(cache1));
        memset(cache2, -1, sizeof(cache2));
        int ans = CountAllTiles(tc[i]) - CountSymTiles(tc[i]);
        (ans < 0) ? ans = ans + 1000000007 : ans = ans;
        //cout << CountAllTiles(tc[i]) - CountSymTiles(tc[i]) << endl;
        cout << ans << endl;
    }
}
