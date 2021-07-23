#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

std::string s;
int cache[41][41][2];

int sol(int start, int end, int is_back) {
    int &ret = cache[start][end][is_back];
    if(ret != -1) return ret;
    if(start > end) return 0;
    if(end - start == 0) return 1;
    if(end - start == 1) {
        if(s[start] <= '2' || (s[start] == '3' && s[end] <= '4')) {
            if(is_back == 1) return 2;
            else return 1;
        }
    }

    ret = 0;
    ret += sol(start, start+0, 0) * sol(start+1, end, 1);
    ret += sol(start, start+1, 0) * sol(start+2, end, 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> s;

    memset(cache, -1, sizeof(cache));
    cout << sol(0, s.size()-1, 1) << endl;
}
