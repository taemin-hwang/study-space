#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
bool is_found = false;
//vector<long long> cache;
long long S(long long start, long long k) {
    if(is_found == true) return 0;
    if(k == 0) {
        if(start + 1 == n) {
            is_found = true;
        }
        //cache.push_back(start+1);
        return 3;
    }

    long long end = S(start, k-1);
    if(start + end + 1 == n) {
        is_found = true;
    }
    //cache.push_back(start + end + 1);
    long long len = 0;
    len += end;
    len += k + 3;
    len += S(start + end + k + 3, k-1);

    return len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    //cout << S(0, 6) << endl;
    S(0, 28);

    //for( auto p : cache ) {
    //    cout << p << " ";
    //}
    //cout << endl;

    if(is_found) cout << "m" << endl;
    else cout << "o" << endl;
}
