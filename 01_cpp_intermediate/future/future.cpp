#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

void worker(std::promise<string>* p) {
    p->set_value("hello");
}

int main() {
    std::promise<string> p;

    std::future<string> data = p.get_future();

    std::thread t(worker, &p);

    cout << data.get() << endl;

    t.join();
}
