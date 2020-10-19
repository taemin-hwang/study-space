// A union is a special data type available that allows to store different data types in the same memory location
// A variant is type-safe union

#include <iostream>
#include <type_traits>
#include <variant>

using namespace std;

int main() {
    variant<int, double, string> v = 123;
    cout << std::get<int>(v) << endl;
    cout << std::get<0>(v) << endl;

    // compile-error: static assertion failed: T should occur for exactly once in alternatives
    // auto f = std::get<float>(v);

    // runtime-error: terminate called after throwing an instance of 'std::bad_variant_access'
    // auto c = std::get<string>(v);
}


