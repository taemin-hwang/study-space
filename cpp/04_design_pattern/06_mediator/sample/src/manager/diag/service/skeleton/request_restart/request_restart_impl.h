#ifndef REQUEST_RESTART_IMPL_H_
#define REQUEST_RESTART_IMPL_H_

#include <functional>
#include <iostream>

class RequestRestartSkeletonImpl {
 public:
    RequestRestartSkeletonImpl();
    virtual ~RequestRestartSkeletonImpl() = default;

    void RequestRestart();

    void Initialize();
    void Run();
    void Shutdown();
    void SetRequestRestartHandler(const std::function<void()>& f);

 private:
    std::function<void()> OnRequestRestart;

};

#endif
