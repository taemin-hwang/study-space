#ifndef DIAG_MANAGER_H_
#define DAIG_MANAGER_H_

#include "mediator/interface/diag_interface.h"
#include "manager/diag/service/diag_skeleton_manager.h"

class DiagManager {
 public:
    DiagManager();
    virtual ~DiagManager() = default;

    void Initialize();
    void Run();
    void Shutdown();
    void SetInterface(std::shared_ptr<DiagInterface> f) { diag_interface_ = f; }
    void OnRequestRestart();

 private:
    std::shared_ptr<DiagInterface> diag_interface_;
    std::unique_ptr<DiagSkeletonManager> diag_skeleton_manager_;
};

#endif
