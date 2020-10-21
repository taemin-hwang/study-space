#include <iostream>

// A literal type is a type that can qualify as constexpr.
// This is true for scalar types, references, certain classes, and arrays of any such types.

using namespace std;

// literal class
class Vector {
 public:
    constexpr Vector(int x, int y) : x_(x), y_(y) {}

    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }

 private:
    int x_;
    int y_;
};

constexpr Vector AddVec(const Vector& v1, const Vector& v2) {
    return { v1.x() + v2.x(), v1.y() + v2.y() };
}

// function object
template <int N>
struct A {
    int operator()() { return N; }
};

int main() {
    constexpr Vector v1{1, 2};
    constexpr Vector v2{3, 4};

    A<v1.x()> a;
    cout << a() << endl;

    A<AddVec(v1, v2).x()> b;
    cout << b() << endl;
}
