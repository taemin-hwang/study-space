#ifndef MEDIATOR_H_
#define MEDIATOR_H_

#include <iostream>
#include <string>

#include "component.h"
class Mediator {
 public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};


#endif
