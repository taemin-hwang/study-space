#ifndef MEDIATOR_H_
#define MEDIATOR_H_

#include <iostream>
#include <string>
#include <vector>

class BaseInterface;
using BaseInterfacePtr = BaseInterface*;

class Mediator {
 public:
    Mediator() = default;
    virtual ~Mediator() = default;

    virtual std::vector<char> HandleReadDid(BaseInterfacePtr sender, int did) = 0;
    virtual void HandleWriteDid(BaseInterfacePtr sender, int did, const std::vector<char>& payload) = 0;
    virtual void HandleRoutineRequest(BaseInterfacePtr sender, int rid, const std::vector<char>& payload) = 0;
    virtual void HandleEnableCondition(BaseInterfacePtr sender, int condition) = 0;
    virtual void HandleSessionControl(BaseInterfacePtr sender, int session) = 0;
};


#endif
