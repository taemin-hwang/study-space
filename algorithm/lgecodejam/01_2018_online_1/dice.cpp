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
bool isFound = false;
int dicesol(int start, int end, int num, int dices) {
    if(isFound) return 1;
    if(num != -1 && num < dices) return 0;
    if(dices == 0) {
        isFound = true;
        return 1;
    }

    int ret = 0;
    for(int i = start ; i < end; i++) {
        if(visit[i] != 0) continue;
        visit[i] = 1;
        if(dicesol(start, end, dice[i], dices-1) > 0) return ret = 1;
        visit[i] = 0;
    }
    return ret;
}

int mindicesol(int start, int end) {
    int& ret = cache[start][end];
    if(start+1 == end) return 1;
    isFound = false;
    if(dicesol(start, end, -1, end-start)) return 1;
    if(ret != -1) return ret;

    ret = INT_MAX;
    int idx = (start + end)/2;
    ret = min(ret, mindicesol(start, idx+1) + mindicesol(idx+1, end));
    return ret;
}

int main() {
    cin >> n;
    dice.resize(n);
    for(int i = 0; i < n ; i++) {
        cin >> dice[i];
    }
    memset(cache, -1, sizeof(cache));
    sort(dice.begin(), dice.end());
    cout << mindicesol(0, n) << endl;
}

