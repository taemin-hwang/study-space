#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
const int INF = 9;
int cache[100][100][100];

vector<pair<int, int>> ans;
vector<vector<int>> hanois;

int dc(int from, int to) {
    cout << from << ", " << to << endl;
    for(int i = 1; i <= 3; i++) {
        for(auto p : hanois[i]) {
            cout << p << " ";
        }
        cout << endl;
    }
    getchar();
    int min_num = INF;

    int top[3];
    for(int i = 1; i <= 3; i++) {
        top[i] = hanois[i].back();
    }
    cout << endl;

    if(cache[top[1]][top[2]][top[3]] != -1) {
        cout << "!!!!!!!!" << endl;
        return min_num;
    }
    cache[top[1]][top[2]][top[3]] = 1;

    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            if(i == j) continue;
            if(i == from && j == to) continue;
            if(top[i] > top[j]) {
                hanois[j].pop_back();
                hanois[i].push_back(top[j]);
                dc(j, i);
                hanois[j].push_back(top[j]);
                hanois[i].pop_back();
            }
        }
    }

    return min_num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;

    memset(cache, -1, sizeof(cache));
    hanois.resize(4);
    hanois[1].push_back(INF);
    hanois[2].push_back(INF);
    hanois[3].push_back(INF);

    for(int i = n; i > 0; i--) {
        hanois[1].push_back(i);
    }

    dc(0, 0);
    //cout << dc(0, 0) << endl;

//    vector<pair<int, int>> ans = dc(0, 0);
//
//    cout << ans.size() << endl;
//    for(auto p : ans) {
//        cout << p.first << " " << p.second << endl;
//    }
}
