#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>
#include <string>
#include "mediator/mediator.h"
#include "mediator/interface/event/event.h"

using namespace std;
class BaseInterface {
 public:
    BaseInterface(Mediator* mediator = nullptr) : mediator_(mediator) { }
    virtual ~BaseInterface() = default;

    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
 protected:
    Mediator* mediator_;
};

#endif
