#include <future>
#include <thread>
#include <chrono>
#include "component/diag/diag_manager.h"

void DiagManager::Run() {
    std::async([=]() {
        while(1) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if(diag_interface_ != nullptr) diag_interface_->ReadDid(100);
        }
    });
}
