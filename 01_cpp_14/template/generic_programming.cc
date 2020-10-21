// template meta programming
// a metaprogramming technique in which templates are used by a compiler to generate temporary source code

#include <iostream>

using namespace std;

template <int N>
struct Int {
    static const int num = N;
};

template <typename T, typename U>
struct add {
    typedef Int<T::num + U::num> result;
};

int main() {
    typedef Int<1> one;
    typedef Int<2> two;

    typedef add<one, two>::result three; // compiler says '3'

    cout << three::num << endl;
}
