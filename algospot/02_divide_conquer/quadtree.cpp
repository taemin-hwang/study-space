#include <iostream>
#include <vector>
#include <string>

using namespace std;

string getPlane(string& s) {
    string ret = "";
    int cnt = 0;
    int xcnt = 0;
    bool isX = false;
    if(s[0] != 'x') {
        ret += s[0];
        s = s.substr(1);
        return ret;
    }
//xxxwwbbbwwwwbb
    ret += s[0];
    for(int i = 1 ; i < s.size(); i++) {
        if(!isX && s[i] != 'x') {
            cnt++;
        } else if(!isX && s[i] == 'x') {
            isX = true;
            xcnt = 0;
        } else if(isX && s[i] != 'x') {
            xcnt++;
            if(xcnt == 4) {
                isX = false;
                xcnt = 0;
                cnt++;
            }
        } else {
            xcnt = 0;
        }
        ret += s[i];

        if(cnt == 4) {
            if(i+1 < s.size())
                s = s.substr(i+1);
            break;
        }
    }
    return ret;
}

void flipTree(string s) {
    if(s[0] == 'w' || s[0] == 'b') {
        cout << s[0];
        return;
    }

    string s1, s2, s3, s4;
    s = s.substr(1);

    cout << "===============" << endl;
    cout << 'x';

    s1 = getPlane(s);
    cout << s1 << ", " << s<< endl;

    s2 = getPlane(s);
    cout << s2 << ", " << s<< endl;

    s3 = getPlane(s);
    cout << s3 << ", " << s<< endl;

    s4 = getPlane(s);
    cout << s4 << ", " << s<< endl;

    flipTree(s3);
    flipTree(s4);
    flipTree(s1);
    flipTree(s2);
}

int main() {
    int C;
    vector<string> tc;

    cin >> C;
    tc.resize(C);
    for(int i = 0; i < C; i++) {
        cin >> tc[i];
    }

    for(auto p : tc) {
        flipTree(p);
        cout << endl;
    }

}
