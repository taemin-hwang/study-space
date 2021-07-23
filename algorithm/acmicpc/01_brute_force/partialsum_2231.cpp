#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for(int i = 1; i <= n; ++i) {
        string s = to_string(i);
        int sum = i;
        for(int j = 0; j < s.size(); ++j) {
            sum += s[j] - '0';
        }
        if(sum == n) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
