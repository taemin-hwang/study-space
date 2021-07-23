#ifndef CONCRETE_COMPONENT_H_
#define CONCRETE_COMPONENT_H_

#include <iostream>
#include <string>
#include "component.h"

using namespace std;

class Component1 : public BaseComponent {
 public:
    void DoA() {
        std::cout << "Component 1 does A" << std::endl;
        this->mediator_->Notify(this, "A");
    }
    void DoB() {
        std::cout << "Component 1 does B" << std::endl;
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent {
 public:
    void DoC() {
        std::cout << "Component 2 does C" << std::endl;
        this->mediator_->Notify(this, "C");
    }
    void DoD() {
        std::cout << "Component 2 does D" << std::endl;
        this->mediator_->Notify(this, "D");
    }
};
#endif

