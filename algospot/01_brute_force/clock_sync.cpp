#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> visit;

void initSwitch(vector<vector<int>>& Switch) {
    Switch.resize(10);
    Switch[0] = {0, 1, 2};
    Switch[1] = {3, 7, 9 ,11};
    Switch[2] = {4, 10, 14, 15};
    Switch[3] = {0, 4, 5, 6, 7};
    Switch[4] = {6, 7, 8, 10, 12};
    Switch[5] = {0, 2, 14, 15};
    Switch[6] = {3, 14, 15};
    Switch[7] = {4, 5, 7, 14, 15};
    Switch[8] = {1, 2, 3, 4, 5};
    Switch[9] = {3, 4, 5, 9, 13};
}

bool isFinished(vector<int>& testcase) {
    for(int i = 0 ; i < testcase.size(); i++) {
        if(testcase[i] != 12) return false;
    }
    return true;
}

void turnOn(vector<int>& testcase, vector<int>& Switch) {
    for(int i = 0 ; i < Switch.size(); i++) {
        testcase[Switch[i]] = (testcase[Switch[i]] + 3) % 12;
        if(testcase[Switch[i]] == 0) testcase[Switch[i]] = 12;
    }
}

void turnOff(vector<int>& testcase, vector<int>& Switch) {
    for(int i = 0 ; i < Switch.size(); i++) {
        testcase[Switch[i]] = testcase[Switch[i]] - 3;
        if(testcase[Switch[i]] == 0) testcase[Switch[i]] = 12;
    }
}

void printTestcase(vector<int>& testcase) {
    cout << "=================" << endl;
    for(int i = 0; i < testcase.size(); i++) {
        if(i % 4 == 0) cout << endl;
        cout.width(3);
        cout << testcase[i] << ", ";
    }
    cout << endl;
}

int ret = INT32_MAX;

void setTwelve(vector<int>& testcase, vector<vector<int>>& Switch, int idx, int trial) {
    if(isFinished(testcase)) {
        if(trial < ret) ret = trial;
        return;
    }

    if(trial > ret) return;
    if(visit[idx] >= 4) return;

    for(int i = idx ; i < 10; i++) {
        turnOn(testcase, Switch[i]);
        visit[idx]++;
        setTwelve(testcase, Switch, i, trial+1);
        turnOff(testcase, Switch[i]);
        visit[idx]--;
    }
}

int main() {
    vector<vector<int>> Switch;
    vector<int> ans;
    initSwitch(Switch);
    visit.resize(10);

    int C, tmp;
    cin >> C;

    vector<vector<int>> testcase;
    testcase.resize(C);

    for(int i = 0 ; i < C; i++) {
        for(int j = 0; j < 16; j++) {
            cin >> tmp;
            testcase[i].push_back(tmp);
        }
    }

    for(int i = 0 ; i < C; i++) {
        ret = INT32_MAX;
        setTwelve(testcase[i], Switch, 0, 0);
        ans.push_back(ret);
    }

    for(auto p : ans) {
        cout << p << endl;
    }

}
