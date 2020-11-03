#ifndef DIAG_HANDLER_H_
#define DIAG_HANDLER_H_

#include <thread>
#include <chrono>
#include "mediator/interface_mediator.h"
#include "component/diag/diag_manager.h"

class DiagHandler {
 public:
    DiagHandler(){
        std::cout << __func__ << std::endl;
        interface_mediator_ = std::make_unique<InterfaceMediator>();
        diag_manager_ = std::make_unique<DiagManager>();
    }

    void Initialize() {
        std::cout << __func__ << std::endl;
        interface_mediator_->Initialize();
        diag_manager_->Initialize();
        diag_manager_->SetInterface(interface_mediator_->GetDiagInterfacePtr());
    }

    void Run() {
        diag_manager_->Run();
        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Shutdown() {
        diag_manager_->Shutdown();
    }

 private:
    std::unique_ptr<InterfaceMediator> interface_mediator_;
    std::unique_ptr<DiagManager> diag_manager_;
    //std::unique_ptr<ViwiManager> viwi_manager_;
    //std::unique_ptr<IpcManager> ipc_manager_;
};

#endif
