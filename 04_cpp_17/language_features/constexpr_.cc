#include <iostream>

using namespace std;

constexpr int Factorial(int n) {
    int total = 1;
    for(int i = 1; i <= n; i++) {
        total *= i;
    }
    return total;
};

template <int N>
struct A {
    int operator()() { return N; }
};

int main() {
    A<Factorial(10)> a;
    cout << a() << endl;
}

#if template_meta_programming
template <int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

template <int N>
struct A {
    int operator()() { return N; }
};

int main() {
    // Template meta progarmming: Factorial<10> is calculated in compile-time
    // operator() is overloaded in class A
    A<Factorial<10>::value> a; // same with A<3628800> a

    cout << a() << endl;
}
#endif

#if run_time
int factorial(int N) {
    int total = 1;
    for(int i = 1; i <= N; ++i) {
        total *= i;
    }
    return total;
}

// function object, functor
template <int N>
struct A {
    int operator()() { return N; }
}

int main() {
    // compile error; factorial(5) is not constexpr
    A<factorial(5)> a;
}
#endif
