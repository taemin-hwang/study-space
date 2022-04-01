#ifndef SHAREDMEMORY_MANAGER_H_
#define SHAREDMEMORY_MANAGER_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "transfer/message_format.h"

class SharedMemoryManager {
 public:
    SharedMemoryManager(int key_id, int size);
    virtual ~SharedMemoryManager();

    void Initialize();
    int SendData(const void *data, int data_size);

 private:
    int key_id_;
    int size_;
    int shmid_;
    void *shared_memory_ = (void *)0;
};


#endif
