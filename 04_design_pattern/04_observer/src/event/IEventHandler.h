#ifndef __IEVENT_HANDLER_H_
#define __IEVENT_HANDLER_H_
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class IEventHandler {
public:
    virtual void execute(int data) = 0;
};

class ConcreteObserverA : public IEventHandler {
public:
    void notify(int data) {
        cout << "A notified : " << data << endl;
    }
};

class ConcreteObserverB : public IEventHandler {
public:
    void execute(int data) {
        cout << "B notified : " << data << endl;
    }
};
#endif
