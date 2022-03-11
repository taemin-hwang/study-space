#ifndef SOCKET_MANAGER_H_
#define SOCKET_MANAGER_H_

#include <iostream>
#include "transfer/message_format.h"

class SocketManager {
 public:
    SocketManager(int port);
    virtual ~SocketManager() = default;

    void Initialize();
    int ReceiveData(const void *data, int data_size);

 private:
    int port_ = 50001;
};


#endif
