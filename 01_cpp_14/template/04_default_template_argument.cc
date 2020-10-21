#include <iostream>

using namespace std;

// functor
template <typename T>
struct Compare {
    bool operator() (const T& a, const T& b) const { return a < b; }
};

// function template
template <typename T, typename Comp>
T Min(T& a, T& b) {
    Comp comp;
    return comp(a, b) ? a : b;
}

// default template argument
template <typename T, typename Comp = Compare<T>>
T dMin(T& a, T& b) {
    Comp comp;
    return comp(a, b) ? a : b;
}

int main() {
    int a = 3, b = 4;
    cout << Min<int, Compare<int>>(a, b) << endl;
    cout << dMin(a, b) << endl;
}
