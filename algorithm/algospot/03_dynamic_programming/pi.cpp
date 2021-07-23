#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

int getLevel(const string& s) {
    int ret = 1;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] != s[i-1]) {
            ret = 2;
            break;
        }
    }
    if(ret == 1) return ret;

    ret = 2;
    for(int i = 1; i < s.size(); i++) {
        if(s[i-1]+1 != s[i]) {
            ret = 4;
            break;
        }
    }
    if(ret == 2) return ret;

    ret = 2;
    for(int i = 1; i < s.size(); i++) {
        if(s[i-1]-1 != s[i]) {
            ret = 4;
            break;
        }
    }
    if(ret == 2) return ret;

    ret = 4;
    for(int i = 1; i < s.size(); i++) {
        if(i % 2 == 0 && s[i] != s[0]) {
            ret = 5; break;
        } else if(i % 2 == 1 && s[i] != s[1]) {
            ret = 5; break;
        }
    }
    if(ret == 4) return ret;

    ret = 5;
    int diff = s[1]-s[0];
    for(int i = 1; i < s.size(); i++) {
        if(s[i-1] + diff != s[i])  {
            ret = 10;
            break;
        }
    }
    if(ret == 5) return ret;

    return 10;
}

int cache[10002];
int getMinLevel(const string s, int start) {
    if(s.size() <= 5) return getLevel(s);

    int &ret = cache[start];
    if(ret != -1) return ret;

    int sz = s.size();
    int ch;
    ret = INT_MAX;

    int tmp = getMinLevel(s.substr(3), start+3);
    if(tmp != INT_MAX) ret = min(ret, getLevel(s.substr(0, 3)) + tmp);

    tmp = getMinLevel(s.substr(4), start+4);
    if(tmp != INT_MAX) ret = min(ret, getLevel(s.substr(0, 4)) + tmp);

    tmp = getMinLevel(s.substr(5), start+5);
    if(tmp != INT_MAX) ret = min(ret, getLevel(s.substr(0, 5)) + tmp);

    return ret;
}

int main() {
    int c;
    vector<string> tc;
    cin >> c;

    tc.resize(c);
    for(int i = 0; i < c; i++) {
        cin >> tc[i];
    }

    for(int i = 0; i < c; i++) {
        memset(cache, -1, sizeof(cache));
        cout << getMinLevel(tc[i], 0) << endl;
    }

}
