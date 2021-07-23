#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> card;
vector<int> cache;
int m;
int recur(int n, int sum) {
    if(n <= 0) {
        if(sum <= m) return sum;
        else return 0;
    }
    int ret = 0;
    for(int i = 0; i < card.size(); ++i) {
        if(cache[i] != 1) {
            cache[i] = 1;
            ret = max(ret, recur(n-1, sum + card[i]));
            cache[i] = 0;
        }
    }
    return ret;
}

int main() {
    int n;
    cin >> n >> m;
    card.resize(n);
    cache.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> card[i];
    }
    cout << recur(3, 0) << endl;
}
