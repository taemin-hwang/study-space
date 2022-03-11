#include "transfer/messagequeue/messagequeue_manager.h"
#include "transfer/utility.h"

void MessageQueueManager::Initialize(){
    std::cout << __func__ << std::endl;
}

int MessageQueueManager::SendData(const void *data, int data_size){
    std::cout << "MessageQueueManager::" << __func__ << std::endl;
    std::cout << "Data Size: " << data_size << std::endl;

    const int *data_ptr = (const int*) data;
    std::cout << "MessageType   : 0x" << std::string(int2hex(data_ptr[0])) << std::endl;
    std::cout << "Payload Length: 0x" << std::string(int2hex(data_ptr[1])) << std::endl;

    return 1;
}