#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    vector<pair<pair<int, int>, int>> people;
    vector<int> ans;
    int n, weight, height;
    cin >> n;

    people.resize(n);
    ans.resize(n);

    for(int i = 0; i < n; ++i) {
        cin >> weight >> height;
        people[i] = {{weight, height}, i};
    }

    sort(people.begin(), people.end(),
        [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
            return (a.first.first > b.first.first) && (a.first.second > b.first.second);
        });

    cout << "============" << endl;
    for(auto p : people) {
        cout << p.second << endl;
    }
    cout << "============" << endl;

    ans[people[0].second] = 1;
    for(int i = 1; i < people.size(); ++i) {
        if((people[i].first.first < people[i-1].first.first) && (people[i].first.second < people[i-1].first.second)) {
            ans[people[i].second] = i + 1;
        } else {
            ans[people[i].second] = ans[people[i-1].second];
        }
    }

    for(auto p : ans) {
        cout << p << " ";
    }

}
