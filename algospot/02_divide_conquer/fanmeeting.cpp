#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

int getCountHug(const string& star, const string& fan) {
    int cnt = 0;
    string starBitStr, fanBitStr, allOneStr;

    starBitStr.resize(star.size());
    for(int i = 0 ; i < star.size(); i++) {
        if(star[i] == 'M') {
            starBitStr[i] = '1';
        } else {
            starBitStr[i] = '0';
        }
        allOneStr.push_back('1');
    }

    fanBitStr.resize(fan.size());
    for(int i = 0 ; i < fan.size(); i++) {
        if(fan[i] == 'M') {
            fanBitStr[i] = '1';
        } else {
            fanBitStr[i] = '0';
        }
    }

    int diff = fan.size() - star.size();

    bitset<200000> starBit(starBitStr);
    bitset<200000> fanBit(fanBitStr);
    bitset<200000> allOne(allOneStr);

    for(int i = 0 ; i <= diff; i++) {
        if((starBit & (fanBit & allOne)) == 0) {
            cnt++;
        }
        fanBit = fanBit >> 1;
    }

    return cnt;
}

int main() {
    int c;
    cin >> c;

    vector<vector<string>> tc;
    tc.resize(c);

    for(int i = 0 ; i < c; i++) {
        tc[i].resize(2);
        cin >> tc[i][0];
        cin >> tc[i][1];
    }

    for(int i = 0; i < c; i++) {
        cout << getCountHug(tc[i][0], tc[i][1]) << endl;
    }
}
