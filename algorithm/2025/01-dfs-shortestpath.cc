#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
int road[100][100];
int visited[100][100];
int min_dist = 12345678;

std::vector<std::pair<int, int>> commands = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_block(int row, int col) {
    for( auto c : commands ) {
        int new_r = row + c.first;
        int new_c = col + c.second;

        if(visited[new_r][new_c] == 0 && road[new_r][new_c] == 1) {
            return false;
        }
    }
    return true;
}

void dfs(int row, int col, int dist) {
    int ret = 0;

    if(row < 0 || col < 0 || row >= N || col >= M) return;
    if(row == N-1 && col == M-1) {
        if (min_dist > dist) {
            min_dist = dist;
        }
    }
    if(is_block(row, col)) return;

    //std::cout << "(" << row << ", " << col << ")" << std::endl;

    visited[row][col] = 1;

    for( auto c : commands ) {
        int new_r = row + c.first;
        int new_c = col + c.second;

        if(visited[new_r][new_c] == 0 && road[new_r][new_c] == 1) {
            //std::cout << "  - (" << new_r << ", " << new_c << ")" << std::endl;
            dfs(new_r, new_c, dist + 1);
        }
    }

    visited[row][col] = 0;

    return;
}

void printroad() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M ; j++) {
            std::cout << road[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {

    cin >> N >> M;

    memset(visited, 0, sizeof(visited));

    int tmp;
    for(int i = 0; i < N; i++) {
        cin >> tmp;
        for(int j = M-1; j >= 0; j--) {
            road[i][j] = tmp % 2;
            tmp = tmp / 10;
        }
    }

    printroad();

    dfs(0, 0, 1);
    if (min_dist == 12345678) cout << -1 << endl;
    else cout << min_dist << endl;
}
