#include <iostream>
#include <memory>
#include "context/context.h"
#include "state/concreteState1.h"
#include "state/concreteState2.h"

using namespace std;

int main() {
    ConcreteState1 s1;
    ConcreteState2 s2;

    unique_ptr<Context> context = make_unique<Context>();
    context->SetState(&s1);
    context->Request();


    context->SetState(&s2);
    context->Request();
}
