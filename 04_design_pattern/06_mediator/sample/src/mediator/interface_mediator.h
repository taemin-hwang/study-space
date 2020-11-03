#ifndef INTERFACE_MEDIATOR_H_
#define INTERFACE_MEDIATOR_H_

#include <iostream>
#include <string>
#include <memory>

#include "mediator/interface/diag_interface.h"
#include "mediator/interface/viwi_interface.h"
#include "mediator/interface/ipc_interface.h"

using DiagInterfacePtr = std::shared_ptr<DiagInterface>;
using ViwiInterfacePtr = std::shared_ptr<ViwiInterface>;
using IpcInterfacePtr = std::shared_ptr<IpcInterface>;

class InterfaceMediator : public Mediator {
 public:
    InterfaceMediator() {
        diag_interface_ = std::make_shared<DiagInterface>();
        viwi_interface_ = std::make_shared<ViwiInterface>();
        ipc_interface_ = std::make_shared<IpcInterface>();
    }
    virtual ~InterfaceMediator() = default;

    void Initialize();
    void Run();
    void Shutdown();
    DiagInterfacePtr GetDiagInterfacePtr() { return diag_interface_; }
    ViwiInterfacePtr GetViwiInterfacePtr() { return viwi_interface_; }
    IpcInterfacePtr GetIpcInterfacePtr() { return ipc_interface_; }

    std::vector<char> HandleReadDid(BaseInterfacePtr sender, int did) override;
    void HandleWriteDid(BaseInterfacePtr sender, int did, const std::vector<char>& payload) override;
    void HandleRoutineRequest(BaseInterfacePtr sender, int rid, const std::vector<char>& payload) override;
    void HandleEnableCondition(BaseInterfacePtr sender, int condition) override;
    void HandleSessionControl(BaseInterfacePtr sender, int session) override;

 private:
    DiagInterfacePtr diag_interface_;
    ViwiInterfacePtr viwi_interface_;
    IpcInterfacePtr  ipc_interface_;
};

#endif
