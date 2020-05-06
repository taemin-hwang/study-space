// NOTE: main function must be written in main.cpp

#include <iostream>
#include <memory>
#include "calc.h"

using namespace std;

int main() {
    unique_ptr<Calc> calc_ = make_unique<Calc>();

    cout << calc_->sum(1, 2) << endl;
    cout << calc_->sub(1, 2) << endl;
}
