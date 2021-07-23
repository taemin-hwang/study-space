#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <numeric>

using namespace std;

int n, k;
int powA[100001];
int powB[100001];
vector<pair<int, int>> diff;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c;
    vector<long long> ans;
    long long valA = 0, valB = 0;

    cin >> c;
    for(int i = 0 ; i < c; i++) {
        cin >> n >> k;
        valA = 0; valB = 0;

        diff.resize(n);
        for(int j = 0; j < n; j++) {
            cin >> powA[j];
            valA += powA[j];
        }
        for(int j = 0; j < n; j++) {
            cin >> powB[j];
            diff[j] = {powA[j]-powB[j], j};
        }

        sort(diff.begin(), diff.end(), [](const pair<int, int>& a, const pair<int, int>& b)->bool{ return a.first < b.first; });

        long long maxVal = 0, tmpVal = 0;
        //cout << valA << ", " << valB << " : " << valA + valB << endl;
        //cout << "=================" << endl;

        for(int j = 0; j < n; j++) {
            valA -= powA[diff[j].second];
            valB += powB[diff[j].second];
            //cout << valA << ", " << valB << " : " << valA + valB << endl;
            tmpVal = valA + valB;
            if(abs(static_cast<int>(n-(j+1)-(j+1))) <= k) {
                //maxVal = max(maxVal, tmpVal);
                if(maxVal < tmpVal) maxVal = tmpVal;
                else break;
            }
        }

        ans.push_back(maxVal);
    }

    for(auto p : ans) {
        printf("%lld\n", p);
    }
}

