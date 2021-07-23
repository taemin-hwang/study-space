#include <iostream>

using namespace std;

namespace foo {
class Foo {
 public:
    void Print() {
        cout << __func__ << endl; // Print
        cout << __FUNCTION__ << endl; // Print
        cout << __PRETTY_FUNCTION__ << endl; // void foo::Foo::Print()
    }
};
}

int main() {
    foo::Foo f;
    f.Print();
}
