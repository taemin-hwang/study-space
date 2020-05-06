#ifndef __CONCRETE_STATE_1_H_
#define __CONCRETE_STATE_1_H_

#include <iostream>
#include "state/Istate.h"
using namespace std;

class ConcreteState1 : public IState {
public:
    ConcreteState1() {}
    ~ConcreteState1() {}

    void handle() override { cout << "State1" << endl;}
};

#endif
