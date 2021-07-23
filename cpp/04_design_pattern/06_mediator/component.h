#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>
#include <string>

using namespace std;
class Mediator;
class BaseComponent {
 public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) { }
    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
 protected:
    Mediator* mediator_;
};

#endif
