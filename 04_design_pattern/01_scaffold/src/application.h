#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

// life cycle of app manager is a sequence of initialize, run and shutdown
class App {
  public:
    App() : exit_requested_(false) { cout << __func__ << endl; }
    ~App() { cout << __func__ << endl; }
    void Initialize() { cout << __func__ << endl; }
    void Run() {
        cout << __func__ << endl;
        while(!exit_requested_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    void Shutdown() { cout << __func__ << endl; }
    void RequestShutdown() {
        cout << __func__ << endl;
        exit_requested_ = true;
    }
  private:
    std::atomic_bool exit_requested_;
};

#endif
