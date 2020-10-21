#ifndef __CONCRETE_STATE_2_H_
#define __CONCRETE_STATE_2_H_

#include <iostream>
#include "state/Istate.h"

using namespace std;

class ConcreteState2 : public IState {
public:
    ConcreteState2() {}
    ~ConcreteState2() {}

    void handle() override { cout << "State2" << endl;}
};

#endif
