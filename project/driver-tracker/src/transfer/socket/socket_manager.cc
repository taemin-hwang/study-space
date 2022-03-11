#include "transfer/socket/socket_manager.h"
#include "transfer/utility.h"

void SocketManager::Initialize(){
    std::cout << __func__ << std::endl;
}

int SocketManager::ReceiveData(const void *data, int data_size){
    std::cout << "SocketManager::" << __func__ << std::endl;
    std::cout << "Data Size: " << data_size << std::endl;

    return 1;
}