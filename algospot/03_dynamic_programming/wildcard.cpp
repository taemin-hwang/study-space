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

    while(idx < wildcard.size() || idx < filename.size()) {
        if(idx >= wildcard.size()) {
            if(filename[idx] == '*') {
                filename = filename.substr(0, idx);
            }
            break;
        }

        if(idx >= filename.size()) {
            if(wildcard[idx] == '*') {
                wildcard = wildcard.substr(0, idx);
            }
            break;
        }

        if(wildcard[idx] != filename[idx]) {
            if(wildcard[idx] != '*' && wildcard[idx] != '?' && filename[idx] != '*' && filename[idx] != '?') {
                break;
            }
            else if(wildcard[idx] == '*' || filename[idx] == '*') {
                if(wildcard[idx] == '*') {
                    char ch = 0;
                    for(int i = idx+1; i < wildcard.size(); i++) {
                        if(wildcard[i] != '*') {
                            ch = wildcard[i];
                            break;
                        }
                    }

                    if(ch == 0) {
                        wildcard = filename;
                        break;
                    } else {

                    }

                } else {

                }
            }
            else if(wildcard[idx] == '?' || filename[idx] == '?') {
                wildcard[idx] = filename[idx];
            }
        }
        idx++;
    }

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
        wildcard[i].resize(0);
        cin >> wildcard[i][0];
        cin >> w;
        filename[i].resize(w);
        for(int j = 0; j < w; j++) {
            cin >> filename[i][j];
        }
    }

    for(int i = 0 ; i < c; i++) {
        vector<string> ans = getMatchedFile(wildcard[i], filename[i]);
        for(auto p : ans) {
            cout << p << endl;
        }
    }

}
