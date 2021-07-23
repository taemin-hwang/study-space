#include <iostream>
#include <string>
#include "concrete_mediator.h"
#include "concrete_component.h"

using namespace std;

int main() {
  Component1 *c1 = new Component1;
  Component2 *c2 = new Component2;
  ConcreteMediator *mediator = new ConcreteMediator(c1, c2);

  std::cout << "Client triggers operation A.\n";
  c1->DoA();
  std::cout << "\n";

  std::cout << "Client triggers operation D.\n";
  c2->DoD();

  delete c1;
  delete c2;
  delete mediator;

}
