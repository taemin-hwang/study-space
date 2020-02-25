#include <iostream>
#include <vector>
#include <string>

using namespace std;

// @brief return plane of string s
string getPlane(string& s) {
    string ret = "";

    ret += s[0];
    s = s.substr(1);

    if(ret == "x") {
        ret += getPlane(s);
        ret += getPlane(s);
        ret += getPlane(s);
        ret += getPlane(s);
    }

    return ret;
}

// @brief flip a sequence of planes from 1,2,3,4 to 3,4,1,2
void flipTree(string s) {
    string s1, s2, s3, s4;

    if(s[0] != 'x') {
        cout << s[0];
        return;
    else {
        cout << 'x';
        s = s.substr(1);
    }

    // s1, s2, s3, s4 means upper-left, upper-right, bottom-left and bottom-right respectively
    s1 = getPlane(s);
    s2 = getPlane(s);
    s3 = getPlane(s);
    s4 = getPlane(s);

    // change sequence from 1,2,3,4 to 3,4,1,2
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
