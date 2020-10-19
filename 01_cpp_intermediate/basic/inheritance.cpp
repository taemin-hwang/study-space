#include <iostream>

class A {
public:
    virtual void Print() { std::cout << "AA" << std::endl; }
};

class B : public A {

};

class C : public B {

};

int main() {
    C c;
    c.Print();
}
