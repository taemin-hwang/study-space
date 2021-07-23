#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

using namespace std;

class Foo {
public:
    Foo() { cout << __func__ << endl; }
    ~Foo() { cout << __func__ << endl; }
};

class Goo {
public:
    Goo() {
        cout << __func__ << endl;
        foo_ = make_unique<Foo>();
    }
    ~Goo() { cout << __func__ << endl; }

private:
    unique_ptr<Foo> foo_;
};

void print() {
    cout << __func__ << endl;
    unique_ptr<Goo> goo_ = make_unique<Goo>();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

int main() {
    std::thread t(print);
    t.detach();

    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    cout << "exit" << endl;
}
