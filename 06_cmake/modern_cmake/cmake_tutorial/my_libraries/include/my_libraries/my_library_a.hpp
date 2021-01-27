#ifndef MY_LIBRARY
#define MY_LIBRARY

#include <iostream>

class MyLibrary {
 public:
    MyLibrary() = default;
    virtual ~MyLibrary() = default;
    static void print();
};

#endif