// NOTE: main function must be written in main.cpp

#include <iostream>
#include <memory>
#include "sample.h"

using namespace std;

int main() {
    MyString mstr("hello");
    cout << mstr.c_string() << endl;

    mstr.Set("gtest");
    cout << mstr.c_string() << endl;
}
