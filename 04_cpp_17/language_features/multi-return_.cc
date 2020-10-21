#include <iostream>
#include <tuple>
#include <string>

using namespace std;

auto foo() {
    struct retvals {
        int i1, i2;
        string str;
    };
    return retvals{10, 20, "hello"};
}

tuple<int, double, string> goo() {
    return {10, 3.14, "world"};
}

int main() {
    auto [i1, i2, str1] = foo();
    cout << i1 << ", " << i2 << ", " << str1 << endl;

    auto [i3, d1, str2] = goo();
    cout << i3 << ", " << d1 << ", " << str2 << endl;
}
