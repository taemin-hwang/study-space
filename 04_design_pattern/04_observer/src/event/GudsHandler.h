#ifndef __GUDS_HANDLER_H_
#define __GUDS_HANDLER_H_
#include <iostream>
#include <vector>
#include <memory>

#include "event/IEventHandler.h"

using namespace std;

class GudsHandler : public IEventHandler {
public:
    void execute(int data = 0) {
        cout << __func__<< " " << data << endl;
    }
};

#endif
