#include <iostream>
#include <string>

template <typename T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
    int a = 1;
    int b = 2;

    std::cout << max<int>(a, b) << std::endl;
    std::cout << max(a, b) << std::endl;
}
