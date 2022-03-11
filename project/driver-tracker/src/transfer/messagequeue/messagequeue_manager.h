#ifndef MESSAGEQUEUE_MANAGER_H_
#define MESSAGEQUEUE_MANAGER_H_

#include <iostream>
#include "transfer/message_format.h"

class MessageQueueManager {
 public:
    MessageQueueManager(int key_id);
    virtual ~MessageQueueManager() = default;

    void Initialize();
    int SendData(const void *data, int data_size);

 private:
    int key_id_;
    key_t mqid_;
};


#endif
