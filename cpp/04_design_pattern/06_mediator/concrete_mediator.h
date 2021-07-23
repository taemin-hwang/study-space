#ifndef CONCRETE_MEDIATOR_H_
#define CONCRETE_MEDIATOR_H_

#include <iostream>
#include <string>

#include "mediator.h"
#include "concrete_component.h"

class ConcreteMediator : public Mediator {
 public:
    ConcreteMediator(Component1 *c1, Component2* c2) : component1_(c1), component2_(c2) {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }

    void Notify(BaseComponent* sender, std::string event) const override {
        if(event == "A") {
            std::cout << "Mediator reacts on event A and triggers following operations" << std::endl;
            this->component2_->DoC();
        }
        if(event == "D") {
            std::cout << "Mediator reacts on event D and triggers following operations" << std::endl;
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }

 private:
    Component1 *component1_;
    Component2 *component2_;
};

#endif
