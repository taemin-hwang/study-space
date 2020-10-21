#ifndef __CONTEXT_H_
#define __CONTEXT_H_

#include "state/Istate.h"

using namespace std;

class Context {
public:
    Context() {}
    ~Context() {}

    void SetState(IState* state) { s = state; }
    void Request() { s->handle(); }

private:
    IState* s;
};

#endif
