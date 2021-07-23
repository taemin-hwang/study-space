#include <memory>
#include <iostream>

using namespace std;

class Foo {
 public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
};

int main() {
    int a = 10;
    {
        std::unique_ptr<Foo> foo = std::make_unique<Foo>();
        int a = 20;
    }
}
