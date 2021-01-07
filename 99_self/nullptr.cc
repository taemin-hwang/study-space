#include <iostream>
#include <memory>

using namespace std;

class Foo {
 public:
    Foo(int d) : d_(d) { cout << __func__ << " (" << d_ << ")" << endl; }
    ~Foo() { cout << __func__ << " (" << d_ << ")" << endl; }
    void Print() { cout << d_ << endl; }
 private:
    int d_;
};

int main() {
    std::unique_ptr<Foo> f = std::make_unique<Foo>(1); // Foo(1)
    f = nullptr; // ~Foo(1) (=reset())
    f = std::make_unique<Foo>(2); // Foo(2)
    f = std::make_unique<Foo>(3); // Foo(3), ~Foo(2)
    f.reset(); // ~Foo(3)
    f = std::make_unique<Foo>(4); // Foo(4)
}
// ~Foo(4)
