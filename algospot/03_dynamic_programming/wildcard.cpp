#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

bool isMatched(string wildcard, string filename) {
    int idx = 0;

    string tmp;

    // compress wildcard
    bool isStar = false;
    for(int i = 0; i < wildcard.size(); i++) {
        if(wildcard[i] == '*') {
            if(isStar) {
                continue;
            }
            isStar = true;
        } else {
            isStar = false;
        }
        tmp.push_back(wildcard[i]);
    }
    wildcard = tmp;

    string wildcardtmp;
    for(int i = 0 ; i < wildcard.size(); i++) {
        if(i == wildcard.size()-1) {
            if(wildcard[i] == '*') filename = wildcard;
        }
        if(wildcard[i] != filename[i]) {
            if(wildcard[i] == '?') {
                filename[i] = wildcard[i];
            } else if(wildcard[i] == '*') {
                char ch = 0;
                for(int j = i+1; j < wildcard.size(); j++) {
                    if(wildcard[j] != '*') {
                        ch = wildcard[j];
                        wildcardtmp = wildcard.substr(j+1);
                        break;
                    }
                }
                if(ch == 0) {
                    filename = wildcard;
                    break;
                } else {
                    if(filename.rfind(ch, filename.size()-1) == string::npos) {
                        break;
                    } else {
                        int idx = filename.rfind(ch, filename.size()-1);
                        tmp = filename.substr(0, idx+1);
                        wildcard = tmp + wildcardtmp;
                        i = idx;
                    }
                }
            } else {
                break;
            }
        }
    }

    //cout << wildcard << ", " << filename << endl;
    return wildcard == filename;
}

vector<string> getMatchedFile(const string& wildcard, const vector<string> filename) {
    vector<string> ret;

    for(int i = 0; i < filename.size(); i++) {
        if(isMatched(wildcard, filename[i])) ret.push_back(filename[i]);
    }

    return ret;
}

int main() {
    vector<vector<string>> filename;
    vector<string> wildcard;
    int c, w;
    cin >> c;

    filename.resize(c);
    wildcard.resize(c);

    for(int i = 0 ; i < c; i++) {
        cin >> wildcard[i];
        cin >> w;
        filename[i].resize(w);
        for(int j = 0; j < w; j++) {
            cin >> filename[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        vector<string> ans = getMatchedFile(wildcard[i], filename[i]);
        sort(ans.begin(), ans.end());
        for(auto p : ans) {
            cout << p << endl;
        }
    }

}
