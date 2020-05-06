#include <iostream>
#include "runtime.h"

std::mutex Runtime::instanceMutex_;

Runtime::Runtime() {
    std::cout << __func__ << std::endl;
}

Runtime::~Runtime() {
    std::cout << __func__ << std::endl;
}

Runtime& Runtime::GetInstance() {
    std::unique_lock<std::mutex> instance_lock(instanceMutex_);
    static Runtime instance_;

    return instance_;
}
