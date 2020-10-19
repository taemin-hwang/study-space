#include <iostream>

// template meta programming
// decrease run time, instead of increasing compile time
template <int N>
struct Factorial {
    static const int result = N * Factorial<N-1>::result;
};

template<>
struct Factorial<1> {
    static const int result = 1;
};

int main() {
    std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
}
