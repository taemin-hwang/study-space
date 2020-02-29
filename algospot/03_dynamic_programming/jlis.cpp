#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
int getJoinedList(vector<int> a, vector<int> b) {
    int ret = 1;
    vector<int> c;
    for(int i = 0 ; i < a.size(); i++)
        c.push_back(a[i]);

    for(int i = 0 ; i < b.size(); i++)
        c.push_back(b[i]);

    sort(c.begin(), c.end());

    for(int i = 1 ; i < c.size(); i++) {
        if(c[i] != c[i-1]) {
            ret++;
        }
    }

    return ret;
}

vector<int> getLis(const vector<int>& tc, int start) {
    vector<int> ret;


    return ret;
}

int main() {
    int a, b, c;
    vector<pair<int, int>> len;
    vector<vector<int>> tc1;
    vector<vector<int>> tc2;

    cin >> c;
    len.resize(c);
    tc1.resize(c);
    tc2.resize(c);
    for(int i = 0 ; i < c; i++) {
        cin >> a >> b;
        len[i] = {a, b};
        tc1[i].resize(a);
        tc2[i].resize(b);

        for(int j = 0; j < a; j++) {
            cin >> tc1[i][j];
        }
        for(int j = 0; j < b; j++) {
            cin >> tc2[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        cout << getJoinedList(getLis(tc1[i], 0), getLis(tc2[i], 0)) << endl;
    }


}

