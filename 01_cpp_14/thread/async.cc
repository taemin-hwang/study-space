#include <iostream>
#include <future>
#include <string>
#include <mutex>

std::mutex m;
struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << " " << i << std::endl;
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << std::endl;
    }
    int goo(int a, int b) {
        return a + b;
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << std::endl;
        return i + 10;
    }
};

// std::launch::deferred : doesn't spawn a new thread, Instead, lazy evaluation is performed
// std::launch::async : spwan a new thread of execution, refurn value will be transfer via std::future

int main() {
    X x;

    // (&x)->foo(42, "Hello")
    auto a1 = std::async(&X::foo, &x, 1, "Hello");

    // return future, and calls x.bar("world") when a2.get() or a2.wait() called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world"); // lazy evaluation

    // calls x.bar("cpp"), a3.get() or a3.wait() doesn't need to be called
    auto a3 = std::async(std::launch::async, &X::bar, x, "cpp"); // concurrent

    // calls X()(43) concurrently, and return future<int>
    auto a4 = std::async(std::launch::async, X(), 2);

    auto a5 = std::async(std::launch::async, &X::goo, &x, 1, 2);

    std::cout << a4.get() << std::endl;
    a2.wait();
    std::cout << a5.get() << std::endl;
}
