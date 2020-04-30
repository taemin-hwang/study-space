#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void print3(int a, int b, int c) {
    cout << "hello " << a << ", " << b << ", " << c << endl;
}

void print0() {
    cout << "hello" << endl;
}

template <typename F, typename ... Args>
void Print(F f, Args... args) {
    //f(args...);
    auto f1 = std::bind(f, args...);
    f1();
}

int main() {
    Print(print3, 10, 20, 30);
    Print(print0);
}
