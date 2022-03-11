#ifndef SOCKET_MANAGER_H_
#define SOCKET_MANAGER_H_

#include <iostream>

class SocketManager {
 public:
    SocketManager() = default;
    virtual ~SocketManager() = default;

    void Initialize();
    int ReceiveData(const void *data, int data_size);
};


#endif
