#include <iostream>

struct Foo {
    inline static int foo = 10;
};

#if _cpp_14_
struct Foo {
    static int foo;
};

int Foo::foo = 10;
#endif

int main() {
    Foo f;
    std::cout << f.foo << std::endl;
}

