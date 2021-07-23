#include "manager/diag/service/diag_skeleton_manager.h"

DiagSkeletonManager::DiagSkeletonManager() {
    request_restart_skeleton_impl_ = std::make_unique<RequestRestartSkeletonImpl>();
}

void DiagSkeletonManager::Initialize() {
    request_restart_skeleton_impl_->Initialize();
}

void DiagSkeletonManager::Run() {
    request_restart_skeleton_impl_->Run();
}

void DiagSkeletonManager::Shutdown() {
    request_restart_skeleton_impl_->Shutdown();
}

void DiagSkeletonManager::SetRequestRestartHandler(const std::function<void()>& f) {
    if(request_restart_skeleton_impl_ != nullptr)
        request_restart_skeleton_impl_->SetRequestRestartHandler(f);
}
