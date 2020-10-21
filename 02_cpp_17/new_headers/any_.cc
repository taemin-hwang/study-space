// any : type-safe void*
#include <iostream>
#include <any>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <typeindex>

using namespace std;

struct Position { double x, y, z; };

int main() {
    any a = std::string("string");
    cout << any_cast<string>(a) << endl;

    // int i = any_cast<int>(a); // bad_any_cast

    a = 123;
    a = Position{1, 2, 3};

    any b;
    cout << b.has_value() << endl; // 0

    b.emplace<string>("hello any");
    cout << b.has_value() << endl; // 1
    cout << b.type().name() << endl; // NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE

    b.reset();
}
