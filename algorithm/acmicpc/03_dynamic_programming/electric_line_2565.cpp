#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

int n;
const int NINF = -123456789;
vector<pair<int, int>> line;

int DP(int A_from, int A_to, int B_from, int B_to) {
    int ret = 0;
    int new_A_from, new_A_to, new_B_from, new_B_to;

    for(int i = 0; i < line.size(); i++) {
        pair<int, int> l = line[i];
        if(A_from == 501 && A_to == -1 && B_from == 501 && B_to == -1) {
            new_A_from = min(l.first, A_from);
            new_A_to = max(l.first, A_to);
            new_B_from = min(l.second, B_from);
            new_B_to = max(l.second, B_to);
            ret = max(ret, DP(new_A_from, new_A_to, new_B_from, new_B_to) + 1);
            continue;
        }

        if((A_from <= l.first && l.first <= A_to) || (B_from <= l.second && l.second <= B_to)) {
            continue;
        } else if((A_from > l.first) && (B_to < l.second)) {
            continue;
        } else if((A_to < l.first) && (B_from > l.second)) {
            continue;
        } else {
            new_A_from = min(l.first, A_from);
            new_A_to = max(l.first, A_to);
            new_B_from = min(l.second, B_from);
            new_B_to = max(l.second, B_to);
            ret = max(ret, DP(new_A_from, new_A_to, new_B_from, new_B_to) + 1);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    int from, to;

    cin >> n;
    line.resize(n);

    for(int i = 0 ; i < n; i++) {
        cin >> from >> to;
        line[i] = {from, to};
    }

    cout << n - DP(501, -1, 501, -1) << endl;
}
