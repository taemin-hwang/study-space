#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

class Foo {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<double, std::milli > milli;
    std::chrono::time_point<clock> beg_;
 public:
    Foo() = default;
    virtual ~Foo() = default;
    void Initialize();
    void SendMessage(const std::string& msg);
    void Run();
    void Timer();

 private:
    std::chrono::time_point<clock> tp;
};

void Foo::Initialize() {
    std::cout << __func__ << std::endl;

    thread t([=]() {Timer();});
    t.detach();
}

void Foo::SendMessage(const std::string& msg) {
    std::cout << __func__ << " : " << msg << std::endl;

     tp = clock::now() + std::chrono::seconds(4);
}

void Foo::Timer() {
    std::cout << __func__ << std::endl;
    while(1) {
        if(tp < clock::now()) {
            SendMessage("hello");
        }
    }
}

void Foo::Run() {
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}

int main() {
    Foo f;
    f.Initialize();
    f.Run();
}
