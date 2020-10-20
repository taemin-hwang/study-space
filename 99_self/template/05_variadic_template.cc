#include <iostream>

template <typename T>
void print(T arg) {
    std::cout << arg << std::endl;
}

// parameter pack : typename...
template <typename T, typename... Types>
void print(T arg, Types... args) {
    std::cout << arg << ", ";
    print(args...);
}

int main() {
    print(1, 3.1, "abc");
    // void print(int arg1, double arg2, const char* arg3)
    // void print(double arg2, const char* arg3)
    // void print(const char* arg3)
}
