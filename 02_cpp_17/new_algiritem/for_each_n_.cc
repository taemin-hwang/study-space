#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    std::vector<int> ns {1, 2, 3, 4, 5};
    for (auto n : ns) std::cout << n << ", ";
    std::cout << std::endl;

    std::for_each_n(ns.begin(), 3, [](auto& n) { n *= 2; });

    for (auto n : ns) std::cout << n << ", "; // 2, 4, 6, 4, 5
    std::cout << std::endl;
}


#if for_each

// UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );

struct Sum {
    void operator()(int n) { sum += n; }
    int sum{0};
}

int main() {
    std::vector<int> nums {3, 4, 2, 8, 15, 267};

    auto print = [](const int& n) { std::cout << " " << n; };

    std::for_each(nums.cbegin(), nums.cend(), print);
}

#endif
