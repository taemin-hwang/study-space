// Template argument deduction (템플릿 인자 추론)
// std::pair p(2, 4.5)
// std::tuple t(4, 3, 2.5);
// std::copy_n(vi1, 3, std::back_insert_iterator(vi2));
// std::for_each(vi.begin(), vi.end(), Foo([&](int i) {...}));

// exmaple
#include <iostream>

using namespace std;

template <typename T>
class Foo {
 public:
    Foo(const T& data) : data(data){}
    T data;
};

int main() {
    //Foo<int> a = 40 // c++14
    Foo a = 42; // c++17
    auto f = Foo{ a.data };
    cout << f.data << endl;
}
