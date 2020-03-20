#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

int n;
vector<int> dice;
int cache[1001][1001];
int visit[1001];

int dicesol(int start, int end, int num, int dices) {
    int& ret = cache[start][end];
    if(num != -1 && num < dices) return ret = 0;
    if(dices == 0) return ret = 1;
    if(ret != -1) return ret;

    ret = 0;
    for(int i = start ; i < end; i++) {
        if(visit[i] != 0) continue;
        visit[i] = 1;
        if(dicesol(start, end, dice[i], dices-1) > 0) return ret = 1;
        visit[i] = 0;
    }
    return ret;
}

int mindicesol(int start, int end) {
    if(start+1 == end) return 1;
    if(dicesol(start, end, -1, end-start)) return 1;

    int ret = INT_MAX;
    for(int i = start; i < end-1; i++) {
        ret = min(ret, mindicesol(start, i+1) + mindicesol(i+1, end));
    }
    return ret;
}

int main() {
    cin >> n;
    dice.resize(n);
    for(int i = 0; i < n ; i++) {
        cin >> dice[i];
    }
    memset(cache, -1, sizeof(cache));
    cout << mindicesol(0, n) << endl;
}

