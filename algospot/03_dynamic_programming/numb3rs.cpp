#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int map[51][51][51];
vector<int> N, D, P;
double getProb(const int& tc, int pos, int d, int sol, const int& p) {
    if(d == 0 && pos == sol) return 1;
    if(d == 0 && pos != sol) return 0;

    double ret = 0.0;
    int cnt = 0;
    for(int i = 0; i < N[tc]; i++) {
        if(map[tc][pos][i] == 1) {
            cnt++;
        }
    }

    for(int i = 0; i < N[tc]; i++) {
        if(map[tc][pos][i] == 1) {
            double tmp = getProb(tc, i, d-1, sol, p);
            ret += tmp / cnt;
        }
    }

    return ret;
}

int main() {
    int c, n, d, p, t, q;
    vector<vector<int>> Q;
    cin >> c;

    Q.resize(c);
    for(int i = 0 ; i < c; i++) {
        cin >> n >> d >> p;
        N.push_back(n);
        D.push_back(d);
        P.push_back(p);
        for(int j = 0 ; j < n; j++) {
            for(int k = 0; k < n; k++) {
                cin >> map[i][j][k];
            }
        }
        cin >> t;
        for(int j = 0; j < t; j++) {
            cin >> q;
            Q[i].push_back(q);
        }
    }

    for(int i = 0; i < c; i++) {
        for(int j = 0; j < Q[i].size(); j++) {
            cout << getProb(i, P[i], D[i], Q[i][j], P[i]) << " ";
        }
        cout << endl;
    }


}
