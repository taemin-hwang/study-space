#include <future>
#include <thread>
#include <chrono>
#include "manager/diag/diag_manager.h"

DiagManager::DiagManager() {
    diag_skeleton_manager_ = std::make_unique<DiagSkeletonManager>();
}

void DiagManager::Initialize() {
    diag_skeleton_manager_->Initialize();
    diag_skeleton_manager_->SetRequestRestartHandler([this]() { this->OnRequestRestart(); });
}

void DiagManager::Run() {
    diag_skeleton_manager_->Run();

    std::async([=]() {
        while(1) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if(diag_interface_ != nullptr) diag_interface_->ReadDid(100);
        }
    });
}

void DiagManager::Shutdown() {
    diag_skeleton_manager_->Shutdown();
    //diag_proxy_manager_->Shutdown();
}

void DiagManager::OnRequestRestart() {
    if(diag_interface_ != nullptr) diag_interface_->RequestRestart();
}

