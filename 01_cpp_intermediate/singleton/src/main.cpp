#include <iostream>
#include "runtime.h"

using namespace std;

int main() {
    Runtime& r1(Runtime::GetInstance());
    Runtime& r2(Runtime::GetInstance());
    //Runtime r3; // error: declared private

    r1.SetData(3);
    r1.PrintData();
    r2.PrintData();
}
