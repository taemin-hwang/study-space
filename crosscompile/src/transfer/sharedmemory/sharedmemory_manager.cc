#include "transfer/sharedmemory/sharedmemory_manager.h"
#include "transfer/utility.h"

SharedMemoryManager::SharedMemoryManager(int key_id, int size) {
    std::cout << "SharedMemoryManager::" << __func__ << std::endl;
    std::cout << "[1] KEY ID    : " << key_id << std::endl;
    std::cout << "[2] SIZE      : " << size << std::endl;
    key_id_ = key_id;
    size_ = size;
    shared_memory_ = malloc(size);
}

SharedMemoryManager::~SharedMemoryManager() {
    std::cout << "SharedMemoryManager::" << __func__ << std::endl;

    if ( -1 == shmctl( shmid_, IPC_RMID, 0)){
        std::cout << "Failed to clear shared memory" << std::endl;
    } else {
        std::cout << "Succeed to clear shared memory" << std::endl;
    }
}

void SharedMemoryManager::Initialize(){
    std::cout << "SharedMemoryManager::" << __func__ << std::endl;
    // Create shared memory
    shmid_ = shmget((key_t)key_id_, size_, 0666|IPC_CREAT);

    if (shmid_ == -1) {
        perror("shmget failed : ");
        exit(0);
    }

    // Attach to process memory
    shared_memory_ = shmat(shmid_, (void *)0, 0);
    if (shared_memory_ == (void *)-1) {
        perror("shmat failed : ");
        exit(0);
    }
}

int SharedMemoryManager::SendData(const void *data, int data_size){
    std::cout << "SharedMemoryManager::" << __func__ << std::endl;
    std::cout << "Data Size: " << data_size << std::endl;

    const int *data_ptr = (const int*) data;
    std::cout << "MessageType   : 0x" << std::string(int2hex(data_ptr[0])) << std::endl;
    std::cout << "Payload Length: 0x" << std::string(int2hex(data_ptr[1])) << std::endl;

    if(data_size == size_) {
        memcpy(shared_memory_, data, data_size);
    } else {
        std::cout << "Data Size Mis-matched" << std::endl;
    }

    return 1;
}