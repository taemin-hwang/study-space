#ifndef IPC_COMPONENT_H_
#define IPC_COMPONENT_H_

#include <iostream>
#include <string>
#include "mediator/interface/interface.h"

using namespace std;

class IpcInterface : public BaseInterface {
 public:
    IpcInterface() {
        std::cout << __func__ << std::endl;
    }
    virtual ~IpcInterface() = default;

    void SetDefaultSession() {
        std::cout << __func__ << std::endl;
        mediator_->HandleSessionControl(this, 3);
    }

    void SendData(int procid, const std::vector<char>& payload) {
        std::cout << __func__ << " : " << procid << std::endl;
    }

    std::vector<char> RecvData(int procid, const std::vector<char>& payload) {
        std::cout << __func__ << " : " << procid << std::endl;
        std::vector<char> res;
        return res;
    }
};
#endif

