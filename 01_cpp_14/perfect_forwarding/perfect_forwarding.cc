#include <iostream>
#include <vector>
#include <functional>
#include <memory>

using namespace std;

class X {
public:
    X(int& a) { cout << "int& " << a << endl; }
    X(int&& a) { cout << "int&& " << a << endl; }
};

// U& is lvalue, so constant '1' cannot assign to arg
#if 0
template<typename T, typename U>
T* Factory(U& arg) {
    return new T(arg);
}

template<typename T, typename U>
T* Factory(const U& arg) {
    return new T(arg);
}
#endif

// std::forward : a single usecase to cast a tgemplated function parameter
// i: int& arg
// 1: int&& arg
template <typename T, typename U>
T* Factory(U&& arg) {
    //return new T(arg); // arg is lvalue
    // U (int&) U&& (int& &&) : lvalue
    // U (int&&) U&& (int&& &&) : rvalue --> perfect forwarding
    return new T(std::forward<U>(arg)); // return new T(static_cast<U&&>(arg));
}

int main() {
    int i = 1;

    X* x1 = Factory<X>(i);
    X* x2 = Factory<X>(1);
}

