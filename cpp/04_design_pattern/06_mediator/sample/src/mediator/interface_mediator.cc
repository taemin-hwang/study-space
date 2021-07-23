#include "mediator/interface_mediator.h"

void InterfaceMediator::Initialize() {
    std::cout << __func__ << std::endl;
    diag_interface_->set_mediator(this);
    viwi_interface_->set_mediator(this);
    ipc_interface_->set_mediator(this);
}

void InterfaceMediator::Run() {}
void InterfaceMediator::Shutdown() {}

std::vector<char> InterfaceMediator::HandleReadDid(BaseInterfacePtr sender, int did) {
    switch(did) {
        default:
            return ipc_interface_->RecvData(0, {});
            break;
    }
}

void InterfaceMediator::HandleWriteDid(BaseInterfacePtr sender, int did, const std::vector<char>& payload) {
    switch(did) {
        default:
            ipc_interface_->SendData(0, {});
            break;
    }
}

void InterfaceMediator::HandleRoutineRequest(BaseInterfacePtr sender, int rid, const std::vector<char>& payload) {

}

void InterfaceMediator::HandleEnableCondition(BaseInterfacePtr sender, int condition) {

}

void InterfaceMediator::HandleSessionControl(BaseInterfacePtr sender, int session) {
    diag_interface_->SetSession(session);
}

