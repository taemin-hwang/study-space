#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int k;
vector<string> tc;

string merge(string& a, string& b) {
    string ret;
    int sz = min(a.size(), b.size());
    int k = -1;
    for(int i = 0; i < sz; i++) {
        //cout << a.substr(a.size()-1-i) << ", " << b.substr(0, i+1) << endl;
        if(a.substr(a.size()-1-i) == b.substr(0, i+1)) {
            k = a.size()-1-i;
        }
    }

    if(a.find(b) != string::npos) {
        return a;
    }

    if(k == -1 || sz == 0) {
        ret = a + b;
    } else {
        ret = a.substr(0, k) + b;
    }

    //cout << a << ", " << b << " : " << ret <<  endl;
    return ret;
}

string restore(string& a, string& b) {
    string ret;
    string s1 = merge(a, b);
    string s2 = merge(b, a);

    if(s1.size() > s2.size()) {
        ret = s2;
    } else {
        ret = s1;
    }
    return ret;
}

int main() {
    int c;
    string tmp;
    vector<string> ans;
    cin >> c;
    for(int i = 0 ; i < c; i++) {
        cin >> k;
        tc.resize(k);
        for(int i = 0 ; i < k; i++) {
            cin >> tc[i];
        }
        tmp = "";
        for(int i = 0 ; i < k; i++) {
            tmp = restore(tmp, tc[i]);
        }
        ans.push_back(tmp);
    }

    for(int i = 0 ; i < c; i++) {
        cout << ans[i] << endl;
    }
}

