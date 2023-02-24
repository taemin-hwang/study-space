#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    v.push_back(6);
    v.erase(v.begin());

    for(const auto& i : v) {
        cout << i << endl;
    }

    auto mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    std::cout << "Mean : " << mean << std::endl;

}
