#include "transfer/transfer_manager.h"
#include "transfer/message_format.h"

void TransferManager::Initialize(){
    std::cout << __func__ << std::endl;
    socket_manager_ = std::make_unique<SocketManager>();
    messagequeue_manager_ = std::make_unique<MessageQueueManager>();
    sharedmemory_manager_ = std::make_unique<SharedMemoryManager>();
}

void TransferManager::Get2DSkeleton(){
    std::cout << __func__ << std::endl;
    int data;
    socket_manager_->ReceiveData(&data, 4);
}

void TransferManager::Send2DSkeleton(int camid, float skeleton_2d[][2]){
    std::cout << __func__ << std::endl;
    struct Skeleton2d data;
    data.camid = camid;
    memcpy(data.body, skeleton_2d, sizeof(data.body));
    sharedmemory_manager_->SendData(&data, sizeof(data));
}

void TransferManager::Send3DSkeleton(float skeleton_3d[][3]){
    std::cout << __func__ << std::endl;
    struct Skeleton3d data;
    memcpy(data.body, skeleton_3d, sizeof(data.body));
    sharedmemory_manager_->SendData(&data, sizeof(data));
}

void TransferManager::SendDriverStatus(int driver_status){
    std::cout << __func__ << std::endl;
    struct DriverStatus data;
    data.status = driver_status;
    sharedmemory_manager_->SendData(&data, sizeof(data));
}

void TransferManager::SendUiControl(int ui_control){
    std::cout << __func__ << std::endl;
    struct UiControl data;
    data.control = ui_control;
    messagequeue_manager_->SendData(&data, sizeof(data));
}