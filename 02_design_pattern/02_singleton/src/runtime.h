#ifndef __RUNTIME_H__
#define __RUNTIME_H__

#include <iostream>
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

class Runtime {
public:
    virtual ~Runtime();
    static Runtime& GetInstance();

private:
    Runtime();
    static std::mutex instanceMutex_;

    Runtime(Runtime&& other) = delete;
    Runtime(const Runtime& other) = delete;
    Runtime& operator=(Runtime&& other) = delete;
    Runtime& operator=(const Runtime& other) = delete;

public:
    inline void SetData(int data) { data_ = data; }
    inline void PrintData() { std::cout << data_ << std::endl; }

private:
    int data_ = 0;
};

#endif
