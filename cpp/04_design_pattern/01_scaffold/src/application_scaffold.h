#ifndef __APPLICATION_SCAFFOLD_H_
#define __APPLICATION_SCAFFOLD_H_

#include <iostream>
#include <atomic>
#include <csignal>
#include <fstream>
#include <utility>
#include <functional>
#include <thread>

using namespace std;

class SignalHandler final {
  public:
    SignalHandler() {
        sigemptyset(&exit_signal_set);
        sigaddset(&exit_signal_set, SIGTERM);
        sigaddset(&exit_signal_set, SIGINT);
    }

    void WaitForExitSignals() {
        running_ = true;
        int signal;
        while(running_) {
            sigwait(&exit_signal_set, &signal);
            switch(signal) {
                case SIGINT:
                    cout << __func__ << " : SIGINT received" << endl;
                    running_ = false;
                    break;
                case SIGTERM:
                    cout << __func__ << " : SIGTERM received" << endl;
                    running_ = false;
                    break;
                default:
                    cout << __func__ << " : " << std::to_string(signal) << " received, but ignored" << endl;
                    break;
            }
        }
    }

    void BlockExitSignals() { pthread_sigmask(SIG_BLOCK, &exit_signal_set, nullptr); }
    void StopWaitingForSignals() {
        if (running_) {
            std::raise(SIGTERM);
        }
    }

  private:
    std::atomic_bool running_{false};
    sigset_t exit_signal_set;
};

template <class Application>
class ApplicationScaffold {
  public:
    static int Launch(int argc, char** argv) {
        SignalHandler signal_handler;
        signal_handler.BlockExitSignals();

        Application app;
        std::thread app_worker(&ApplicationScaffold::Execute, std::ref(app), std::ref(signal_handler));

        signal_handler.WaitForExitSignals();
        app.RequestShutdown();

        app_worker.join();

        return 0;
    }

    static void Execute(Application& app, SignalHandler& signal_handler) {
        try {
            app.Initialize();
            app.Run();
        } catch (const std::system_error& sys_exception) {
            cerr << __func__ << " system_error exception" << endl;
        } catch (const std::exception& ex) {
            cerr << __func__ << " " << ex.what() << " exception" << endl;
        }
        app.Shutdown();
        signal_handler.StopWaitingForSignals();
    }
};

#endif
