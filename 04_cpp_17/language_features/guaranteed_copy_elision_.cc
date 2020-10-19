// copy elision (복사 생략)
#include <iostream>

using namespace std;

// Copy Elision
struct Foo {
    Foo() { std::cout << "Contructor" << std::endl; }
    Foo(const Foo&) { std::cout << "Copy-constructor" << std::endl; }
    Foo(Foo&&) { std::cout << "Move-constructor" << std::endl; }
    ~Foo() { std::cout << "Distructor" << std::endl; }
};

// Return Value Optimization
Foo RVO_f() {
    return Foo();
}

// Named Return Value Optimization
Foo NRVO_f() {
    Foo foo;
    return foo;
}

// Guaranted Copy Elision
struct Goo {
    Goo() { std::cout << "Contructor" << std::endl; }
    Goo(const Goo&) = delete;
    Goo(Goo&&) = delete;
    ~Goo() { std::cout << "Distructor" << std::endl; }
};

Goo RVO_g() {
    return Goo();
}


// -fno-elide-constructors
int main() {
    Goo grvo = RVO_g(); // c14 compile error : use of deleted function
    Foo rvo = RVO_f(); // Copy constructor elision
    Foo nrvo = NRVO_f(); // Copy constructor elision
}
