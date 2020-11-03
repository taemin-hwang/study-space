#ifndef DIAG_MANAGER_H_
#define DAIG_MANAGER_H_

#include "mediator/interface/diag_interface.h"

class DiagManager {
 public:
    DiagManager() = default;
    virtual ~DiagManager() = default;

    void Initialize() {}
    void Run();
    void Shutdown() {}
    void SetInterface(std::shared_ptr<DiagInterface> f) { diag_interface_ = f; }
 private:
    std::shared_ptr<DiagInterface> diag_interface_;
};

#endif
