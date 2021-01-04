#include <iostream>

using namespace std;

void foo(int& a) {
    cout << "lvalue reference" << endl;
}

void foo(int&& a) {
    cout << "rvalue reference" << endl;
}

int main() {
    int a = 10;
    int& lref = a;
    int&& rref = 10;

    cout << lref << endl;
    cout << rref << endl;

    foo(a);
    foo(10);
    foo(lref);
    foo(rref);
}
