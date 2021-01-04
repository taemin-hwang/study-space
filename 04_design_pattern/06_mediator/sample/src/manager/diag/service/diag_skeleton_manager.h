#ifndef DIAG_SKELETON_MANAGER_H_
#define DIAG_SKELETON_MANAGER_H_

#include <functional>
#include <memory>
#include "manager/diag/service/skeleton/request_restart/request_restart_impl.h"

class DiagSkeletonManager {
 public:
    DiagSkeletonManager();
    virtual ~DiagSkeletonManager() = default;

    void Initialize();
    void Run();
    void Shutdown();
    void SetRequestRestartHandler(const std::function<void()>& f);

 private:
    std::unique_ptr<RequestRestartSkeletonImpl> request_restart_skeleton_impl_;
};

#endif
