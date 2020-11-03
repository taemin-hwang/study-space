#ifndef DIAG_COMPONENT_H_
#define DIAG_COMPONENT_H_

#include <iostream>
#include <string>
#include "mediator/interface/interface.h"

using namespace std;

class DiagInterface : public BaseInterface {
 public:
    DiagInterface() {
        std::cout << __func__ << std::endl;
    }
    virtual ~DiagInterface() = default;

    void SetSession(int session) {
        std::cout << __func__ << " : " << session << std::endl;
        // TODO: set diagnostic session
    }
    void ReadDid(int did) {
        std::cout << __func__ << std::endl;
        std::vector<char> res = mediator_->HandleReadDid(this, did);
    }
    void WriteDid(int did, const std::vector<char>& payload) {
        std::cout << __func__ << std::endl;
        mediator_->HandleWriteDid(this, did, payload);
    }
};
#endif

