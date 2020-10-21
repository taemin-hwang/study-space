#ifndef __ISTATE_H_
#define __ISTATE_H_

class IState {
public:
    IState() {}
    ~IState() {}

    virtual void handle() = 0;
};

#endif
