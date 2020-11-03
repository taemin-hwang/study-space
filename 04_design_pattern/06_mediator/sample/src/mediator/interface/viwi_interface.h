#ifndef VIWI_COMPONENT_H_
#define VIWI_COMPONENT_H_

#include <iostream>
#include <string>
#include "mediator/interface/interface.h"

using namespace std;

class ViwiInterface : public BaseInterface {
 public:
    ViwiInterface() {
        std::cout << __func__ << std::endl;
    }
    virtual ~ViwiInterface() = default;

    void ShowVehicleService() {
        std::cout << __func__ << std::endl;
    }
};
#endif

