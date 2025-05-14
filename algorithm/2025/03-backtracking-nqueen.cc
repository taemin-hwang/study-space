#include <iostream>
#include <vector>
#include <cstring>

int map[15][15];

using namespace std;

bool is_safe(int row, int col, int N) {
    for(int i = 0; i < N; i++) {
        if(map[row][i] == 1) return false;
    }

    for(int i = 0; i < N; i++) {
        if(map[i][col] == 1) return false;
    }

    for(int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
        if(map[i][j] == 1) return false;
    }

    for(int i = row-1, j = col+1; i >=0 && j < N; i--, j++) {
        if(map[i][j] == 1) return false;
    }

    return true;
}

int dfs(int row, int col, int cnt, const int& n ) {
    int ret = 0;

    if(!is_safe(row, col, n)) return 0;
    std::cout << "(" << row << ", " << col << ") : " << cnt << std::endl;
    if(cnt == n) {
        return 1;
    }

    map[row][col] = 1;

    int next = row + 1;
    for(int i = 0; i < n; i++) {
        ret += dfs(next, i, cnt+1, n);
    }

    map[row][col] = 0;
    return ret;
}

int totalNQueens(int n) {
    int ret = 0;

    for(int i = 0; i < n; i++) {
        std::cout << "===============" << std::endl;
        ret += dfs(0, i, 1, n);
    }

    return ret;
}

int main() {
    int N;
    cin >> N;

    memset(map, 0, sizeof(map));

    if (N > 15) {
        std::cout << "exceed the maximum limits" << std::endl;
        return 0;
    }

    std::cout << totalNQueens(N) << std::endl;
}
