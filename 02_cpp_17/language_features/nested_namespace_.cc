#include <iostream>
using namespace std;

namespace A::B {
class Foo {
 public:
    Foo(int data) { cout << data << endl; }
};
}


#if _cpp_14_
namespace A {
namespace B {
class Foo {
 public:
    Foo(int data) { cout << data << endl; }
};
}
}
#endif

int main() {
    auto f = A::B::Foo(1);
}
