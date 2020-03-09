#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

double cache[501][501];
int m, q, sz;
double B[501];
double T[501][501];
double M[501][501];
int t[501];
double prob[501];
vector<string> ref;
vector<string> tc;

double ocr(int idx, int prev) {
    double& ret = cache[idx][prev];
    if(idx == sz) return ret = 1;
    if(ret >= 0) return ret;

    auto itr = find(ref.begin(), ref.end(), tc[idx]);
    int curr = itr - ref.begin();
    int bestIdx = 0;
    ret = 0;
    if(idx == 0) {
        for(int i = 0; i < m; i++) {
            double tmp = M[i][curr] * B[i] * ocr(idx+1, i);
            if(ret < tmp) {
                ret = tmp;
                bestIdx = i;
            }
        }
    } else {
        for(int i = 0; i < m; i++) {
            double tmp = M[i][curr] * T[prev][i] * ocr(idx+1, i);
            if(ret < tmp) {
                ret = tmp;
                bestIdx = i;
            }

            //if(idx == 1) {
            //    cout << idx << ": " << "T[" << prev << "]["<< i <<"] : " << T[prev][i] << endl;
            //    cout << idx << ": " << "M[" << i << "]["<< curr <<"] : " << M[i][curr] << endl;
            //    cout << "ocr : " << ocr(idx+1, i) << endl;
            //    cout << "bestIdx " << bestIdx << endl;
            //    getchar();

            //}
        }
    }

    // key point
    if(prob[idx] < ret) {
        t[idx] = bestIdx;
        prob[idx] = ret;
    }
    return ret;
}


int main() {
    vector<vector<string>> ans;
    cin >> m >> q;

    ref.resize(m);
    ans.resize(q);

    for(int i = 0; i < m; i++)
        cin >> ref[i];

    for(int i = 0; i < m; i++)
        cin >> B[i];

    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            cin >> T[i][j];

    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            cin >> M[i][j];

    for(int i = 0; i < q; i++) {
        cin >> sz;
        tc.resize(sz);
        for(int j = 0; j < sz; j++) {
            cin >> tc[j];
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                cache[i][j] = -1;
            }
        }
        ocr(0, 0);

        for(int j = 0; j < sz; j++) {
            ans[i].push_back(ref[t[j]]);
        }
    }

    for(int i = 0; i < q; i++) {
        for(int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

}
