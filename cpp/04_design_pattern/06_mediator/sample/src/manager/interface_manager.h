#ifndef _INTERFACE_MANAGER_H_
#define _INTERFACE_MANAGER_H_

#include <memory>
#include "manager/diag/diag_manager.h"
#include "mediator/interface_mediator.h"

class InterfaceManager {
 public:
    InterfaceManager(std::shared_ptr<InterfaceMediator> mediator) : interface_meidator_(mediator) {
        diag_manager_ = std::make_unique<DiagManager>();
    }
    virtual ~InterfaceManager() = default;
    void Initialize() {
        diag_manager_->Initialize();
    }
    void Run() {
        diag_manager_->Run();
    }
    void Shutdown() {
        diag_manager_->Shutodown();
    }

 private:
    std::shared_ptr<InterfaceMediator> interface_mediator_;
    std::unique_ptr<DiagManager> diag_manager_;
};

#endif
