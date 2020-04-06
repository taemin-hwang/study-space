#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int n;
vector<pair<char, char>> user1;
vector<pair<char, char>> user2;

int main() {
    int c;
    string card;
    bool is_valid = true;
    vector<string> ans;
    cin >> c;

    for(int i = 0 ; i < c; i++) {
        is_valid = true;
        cin >> n;
        user1.resize(n);
        user2.resize(n);

        for(int j = 0; j < n; j++) {
            cin >> card;
            user1[j] = {card[0], card[1]};
        }

        for(int j = 0; j < n; j++) {
            cin >> card;
            user2[j] = {card[0], card[1]};
        }

        sort(user1.begin(), user1.end());
        sort(user2.begin(), user2.end());

        for(int j = 0; j < n; j++) {
            if(user1[j].first == user2[j].first && user1[j].second == user2[j].second) {
                continue;
            } else {
                is_valid = false;
                break;
            }
        }

        if(is_valid) {
            ans.push_back("NOT CHEATER");
        } else {
            ans.push_back("CHEATER");
        }
    }

    for(auto p : ans) {
        cout << p << endl;
    }
}
