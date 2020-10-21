#include <algorithm>
#include <vector>
#include <random>
#include <numeric>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
    std::vector<int> in(45); // initialize vector with size 45
    iota(in.begin(), in.end(), 1); // {1, 2, 3, 4, 5, ... , 45} : <numeric>

    std::vector<int> out;

    for(int i = 0; i < 5; i++) {
        out.clear();
        // std::random_device <random>
        std::sample(in.begin(), in.end(), std::back_inserter(out), 6, std::mt19937{std::random_device{}()});

        for(auto o : out) cout << o << "\t";
        cout << endl;
    }
}
