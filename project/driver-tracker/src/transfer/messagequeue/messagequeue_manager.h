#ifndef MESSAGEQUEUE_MANAGER_H_
#define MESSAGEQUEUE_MANAGER_H_

#include <iostream>

class MessageQueueManager {
 public:
    MessageQueueManager() = default;
    virtual ~MessageQueueManager() = default;

    void Initialize();
    int SendData(const void *data, int data_size);
};


#endif
