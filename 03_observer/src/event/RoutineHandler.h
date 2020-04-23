#ifndef __ROUTINE_HANDLER_H_
#define __ROUTINE_HANDLER_H_
#include <iostream>
#include <vector>
#include <memory>

#include "event/IEventHandler.h"

using namespace std;

class RoutineHandler : public IEventHandler {
public:
    RoutineHandler(int rid) : rid_(rid) {}
    void execute(int data) {
        print();
        cout << __func__ << " " << data << endl;
    }
private:
    inline void print() { cout << "rid: " << rid_ << endl; }
    int rid_;
};
#endif

