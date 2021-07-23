#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int n, m;
long long dist[101][101];

void floyd() {
    for(int via = 1; via <= n; ++via) {
        for(int here = 1; here <= n; ++here) {
            for(int there = 1; there <=n; ++there) {
                if(dist[here][there] > dist[here][via] + dist[via][there]) {
                    dist[here][there] = dist[here][via] + dist[via][there];
                }
            }
        }
    }

    for(int here = 1; here <= n; ++here) {
        for(int there = 1; there <= n; ++there) {
            if(dist[here][there] >= 30000000) {
                dist[here][there] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int here, there, weight;
    cin >> n;
    cin >> m;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <=n; ++j) {
            dist[i][j] = 30000000;
            if(i == j) {
                dist[i][j] = 0;
            }
        }
    }

    for(int i = 0 ; i < m; ++i) {
        cin >> here >> there >> weight;
        if(dist[here][there] > weight) {
            dist[here][there] = weight;
        }
    }

    floyd();

    for(int here = 1; here <= n; ++here) {
        for(int there = 1; there <=n; ++there) {
            cout << dist[here][there] << " ";
        }
        cout << endl;
    }
}
