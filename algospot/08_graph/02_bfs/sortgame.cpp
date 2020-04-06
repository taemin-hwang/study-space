#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>

using namespace std;

int n;
set<vector<int>> visit;
int bfs(const vector<int>& order, const vector<int>& prob) {
    int path = 0;
    queue<pair<vector<int>, int>> q;
    q.push({order, 0});
    visit.insert(order);

    while(!q.empty()) {
        pair<vector<int>, int> tmp = q.front();
        //for(auto p : tmp.first) {
        //    cout << p << " ";
        //}
        //cout << endl;
        //cout << tmp.second << endl;
        //getchar();
        if(tmp.first == prob) {
            path = tmp.second;
            break;
        }

        q.pop();
        visit.insert(tmp.first);


        for(int i = 1 ; i < order.size(); i++) {
            pair<vector<int>, int> swaps = tmp;
            vector<int> swaps_vec = swaps.first;
            for(int begin = 0; begin <= order.size(); begin++) {
                for(int end = begin; end <= order.size(); end++) {
                    swaps_vec = swaps.first;
                    reverse(swaps_vec.begin() + begin, swaps_vec.begin()+end);
                    if(visit.find(swaps_vec) == visit.end()) {
                        q.push({swaps_vec, swaps.second+1});
                        visit.insert(swaps_vec);
                    }
                }
            }
        }
    }

    return path;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c;
    vector<int> ans, prob, order;

    cin >> c;
    for(int i = 0 ; i < c; i++) {
        cin >> n;
        prob.resize(n);
        for(int j = 0; j < n; j++) {
            cin >> prob[j];
        }
        order = prob;
        sort(order.begin(), order.end());
        ans.push_back(bfs(order, prob));
    }

    for(auto p : ans) {
        cout << p << endl;
    }
}
