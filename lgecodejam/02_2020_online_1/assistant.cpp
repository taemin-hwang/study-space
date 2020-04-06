#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int adj[3][10001];
int num_edge[10001];
vector<int> n_room(3);
vector<int> m_room(3);

vector<pair<int, char>> sol() {
    vector<pair<int, char>> ret;

    //for(int room = 0; room < 3; room++) {
    //    if(n_room[room] >= m_room[room]) {
    //        for(int person = 0; person <= n; person++) {
    //            if(adj[room][person] == 1) {
    //                for(int i = 0; i < 3; i++) {
    //                    if(adj[i][person] == 1) {
    //                        adj[i][person] = 0;
    //                        m_room[i]--;
    //                    }
    //                }
    //                ret.push_back({person, room+'A'});
    //            }
    //        }
    //        n_room[room] = 0;
    //        m_room[room] = INT_MAX;
    //    }
    //}

    //for(int person = 0; person <= n; person++) {
    //    for(int room = 0; room < 3; room++) {
    //        if(adj[room][person] > 0) {
    //            num_edge[person]++;
    //        }
    //    }
    //}

    //for(int room = 0; room < 3; room++) {
    //    for(int person = 0; person <= n; person++) {
    //        if(n_room[room] > 0 && adj[room][person] == 1 && num_edge[person] == 1) {
    //            n_room[room]--;
    //            num_edge[person]--;
    //            adj[room][person] = 0;
    //            m_room[room] = INT_MAX;
    //            ret.push_back({person, room+'A'});
    //        }
    //    }
    //}

    //int max_ret = 0;
    //for(int person = 0; person <= n; person++) {
    //    for(int room = 0; room < 3; room++) {
    //        if(adj[room][person] > 0) {
    //            max_ret++;
    //            break;
    //        }
    //    }
    //}


    for(int person = 0; person <= n; person++) {
        int min_m = INT_MAX;
        int min_room;
        for(int room = 0; room < 3; room++) {
            if(adj[room][person] > 0) {
                if(n_room[room]> 0 && m_room[room] > 0 && min_m > m_room[room]) {
                    min_m = m_room[room];
                    min_room = room;
                }
            }
        }
        //cout << person << ": " << min_room << endl;
        //cout << "n : " << n_room[0] << ", " << n_room[1] << ", " << n_room[2] << endl;
        //cout << "m : " << m_room[0] << ", " << m_room[1] << ", " << m_room[2] << endl;
        //cout << "==============================" << endl;
        if(min_m != INT_MAX) {
            if(n_room[min_room] > 0) {
                for(int i = 0; i < 3; i++) {
                    if(adj[i][person] == 1) {
                        adj[i][person] = 0;
                        m_room[i]--;
                    }
                }
                n_room[min_room]--;
                ret.push_back({person, min_room+'A'});
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int c, tmp;
    vector<vector<pair<int, char>>> ans;
    cin >> c;

    for(int i = 0; i < c; i++) {
        cin >> n;
        cin >> n_room[0] >> n_room[1] >> n_room[2];
        for(int room = 0; room < 3; room++) {
            cin >> m_room[room];
            for(int person = 0 ; person < m_room[room]; person++) {
                cin >> tmp;
                adj[room][tmp] = 1;
            }
        }

        ans.push_back(sol());
    }

    for(int i = 0; i < ans.size() ; i++) {
        cout << ans[i].size() << endl;
        for(auto p : ans[i]) {
            cout << p.first << " " << p.second << endl;
        }
    }
}
