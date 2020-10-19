#include <iostream>
#include <memory>

using namespace std;

// static_assert( cosntant-expression, string-literal );
// compiler will check assertion in compile-time, not run-time

// #pragma pack(1)
struct Command {
    char cmd;
    int len;
};

template <class T>
void foo(T& a) {
    static_assert(sizeof(Command) == sizeof(a.cmd) + sizeof(a.len));
}

int main() {
    Command a;
    foo(a);
}
