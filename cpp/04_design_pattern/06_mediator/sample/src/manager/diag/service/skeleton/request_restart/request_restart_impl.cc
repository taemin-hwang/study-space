#include <future>
#include <thread>
#include <chrono>

#include "manager/diag/service/skeleton/request_restart/request_restart_impl.h"

RequestRestartSkeletonImpl::RequestRestartSkeletonImpl() {

}

void RequestRestartSkeletonImpl::Initialize() {

}

void RequestRestartSkeletonImpl::Run() {
    std::async([=]() {
        while(1) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            RequestRestart();
        }
    });
}

void RequestRestartSkeletonImpl::SetRequestRestartHandler(const std::function<void()>& f) {
    std::cout << __func__ << std::endl;
    OnRequestRestart = f;
}

void RequestRestartSkeletonImpl::RequestRestart() {
    if(OnRequestRestart != nullptr) {
        OnRequestRestart();
    }
}
