// packaged_task
// promise + callable
// automatically set_value of promise when callable returns
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int twosum (int a, int b) {
    return a + b;
}

int main ()
{
    std::packaged_task<int(int,int)> tsk (twosum);
    std::future<int> ret = tsk.get_future();

    // copy constructor of packaged_task was deleted, need to call explicit move constructor
    std::thread t (std::move(tsk),2,3);

    // ...

    std::cout << ret.get() << std::endl;
    t.join();

    return 0;
}
