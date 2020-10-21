// kinds of unpack
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main() {
    // template argument deduction
    auto t1 = std::make_tuple(1, 'a', 2.3); // c++17
    auto t2 = std::make_tuple(2, 'b', 3.3); // c++17

    auto [i, c, d] = t1; // structed binding
    std::cout << i << ", " << c << ", " << d << endl;

    auto& [ii, cc, dd] = t2; // referenced unpack (auto&)

    std::cout << ii << ", " << cc << ", " << dd << endl;
    ii++;
    std::cout << std::get<0>(t2) << std::endl;

    return 0;
}

#if _struct_example_
struct Foo {
    int i;
    char c;
    double d;
};

int main() {
    Foo f1{1, 'a', 2.3};
    auto [i, c, d] = f1;
    std::cout << i << ", " << c << ", " << d << std::endl;

    Foo f2{2, 'b', 3.3};
    auto& [ii, cc, dd] = f2;

    std::cout << ii << ", " << cc << ", " << dd << endl;
    ii++;
    std::cout << f2.i << std::endl;

    return 0;
}

#endif

#if _cpp_14_

int main() {
    auto tuple = std::make_tuple<int, char, double>(1, 'a', 2.3); // c++14
    auto tuple = std::make_tuple(1, 'a', 2.3);

    int i;
    char c;
    double d;

    std::tie(i, c, d) = tuple;
    std::cout << i << ", " << c << ", " << d << endl;

    return 0;
}

#endif

#if _cpp_14_

int main() {
    auto tuple = std::make_tuple<int, char, double>(1, 'a', 2.3); // c++14
    auto tuple = std::make_tuple(1, 'a', 2.3);

    auto& i = std::get<0>(tuple);
    auto& c = std::get<1>(tuple);
    auto& d = std::get<2>(tuple);

    i = 2;

    std::cout << std::get<0>(tuple) << std::endl;

    return 0;
}

#endif

