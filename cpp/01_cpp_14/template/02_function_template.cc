#include <iostream>
#include <string>

template <typename T>
T max(T& a, T& b) {
    return a > b ? a : b;
}

int main() {
    int a = 1, b = 2;

    // std::cout << max<int>(a, b) << std::endl;
    std::cout << max(a, b) << std::endl;
}
