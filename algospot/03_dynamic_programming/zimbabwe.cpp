#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int c, m, ans;
    string e, es;
    cin >> c;
    vector<int> ret;

    for(int i = 0; i < c; i++) {
        cin >> e >> m;
        es = e;
        ans = 0;
        sort(e.begin(), e.end());
        do {
            if(e == es) {
                break;
            }

            if(stol(e) % m == 0) {
                ans++;
                ans%= 1000000007;
            }

        } while(next_permutation(e.begin(), e.end()));
        ret.push_back(ans);
    }

    for(int i = 0 ; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
}

