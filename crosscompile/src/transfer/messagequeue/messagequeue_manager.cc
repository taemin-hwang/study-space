#include "transfer/messagequeue/messagequeue_manager.h"
#include "transfer/utility.h"

MessageQueueManager::MessageQueueManager(int key_id) {
    std::cout << "MessageQueueManager::" << __func__ << std::endl;
    std::cout << "[1] KEY ID    : " << key_id << std::endl;
    key_id_ = key_id;
}

void MessageQueueManager::Initialize(){
    std::cout << "MessageQueueManager::" << __func__ << std::endl;
    mqid_ = msgget((key_t)key_id_, IPC_CREAT|0666);
    if (mqid_ == -1) {
        perror("msgget error : ");
    }

    std::cout << "MessageQueue id : " << mqid_ << std::endl;
}

int MessageQueueManager::SendData(const void *data, int data_size){
    std::cout << "MessageQueueManager::" << __func__ << std::endl;
    std::cout << "Data Size: " << data_size << std::endl;

    const int *data_ptr = (const int*) data;
    std::cout << "MessageType   : 0x" << std::string(int2hex(data_ptr[0])) << std::endl;
    std::cout << "Payload Length: 0x" << std::string(int2hex(data_ptr[1])) << std::endl;

    if (msgsnd( mqid_, data, data_size, IPC_NOWAIT) == -1) {
        perror("msgsnd error : ");
        return 0;
    }

    return 1;
}