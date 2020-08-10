#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int home[17][17];
int cache[17][17][3];
int n;

bool is_out_of_range(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= n) return true;
    else return false;
}

enum class POS : int {HORI = 0, VERT = 1, DIAG = 2};

int sol(int x, int y, POS pos) {
    if(is_out_of_range(x, y)) return 0;
    if(x == n-1 && y == n-1) return 1;

    int & ret = cache[x][y][static_cast<int>(pos)];
    if(ret != -1) return ret;
    ret = 0;

    int nx, ny;

    switch(pos) {
        case POS::HORI:
            nx = x;
            ny = y+1;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0) {
                    ret += sol(nx, ny, POS::HORI);
                }
            }
            nx = x+1;
            ny = y+1;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0 && home[nx-1][ny] == 0 && home[nx][ny-1] == 0) {
                    ret += sol(nx, ny, POS::DIAG);
                }
            }
            break;

        case POS::VERT:
            nx = x+1;
            ny = y;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0) {
                    ret += sol(nx, ny, POS::VERT);
                }
            }
            nx = x+1;
            ny = y+1;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0 && home[nx-1][ny] == 0 && home[nx][ny-1] == 0) {
                    ret += sol(nx, ny, POS::DIAG);
                }
            }
            break;


        case POS::DIAG:
            nx = x;
            ny = y+1;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0) {
                    ret += sol(nx, ny, POS::HORI);
                }
            }
            nx = x+1;
            ny = y;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0) {
                    ret += sol(nx, ny, POS::VERT);
                }
            }
            nx = x+1;
            ny = y+1;
            if(is_out_of_range(nx, ny) == false) {
                if(home[nx][ny] == 0 && home[nx-1][ny] == 0 && home[nx][ny-1] == 0) {
                    ret += sol(nx, ny, POS::DIAG);
                }
            }
            break;

        default:
            break;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0 ; j < n; j++) {
            cin >> home[i][j];
        }
    }
    memset(cache, -1, sizeof(cache));
    home[0][0] = 1;
    cout << sol(0, 1, POS::HORI) << endl;
}
