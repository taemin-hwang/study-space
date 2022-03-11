#ifndef SHAREDMEMORY_MANAGER_H_
#define SHAREDMEMORY_MANAGER_H_

#include <iostream>

class SharedMemoryManager {
 public:
    SharedMemoryManager() = default;
    virtual ~SharedMemoryManager() = default;

    void Initialize();
    int SendData(const void *data, int data_size);
};


#endif
