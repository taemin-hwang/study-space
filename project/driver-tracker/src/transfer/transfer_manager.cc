#include "transfer/transfer_manager.h"
#include "transfer/message_format.h"

TransferManager::TransferManager(){
    std::cout << __func__ << std::endl;
    sk_manager_ = std::make_unique<SocketManager>(50001);
    mq_manager_ = std::make_unique<MessageQueueManager>(50002);
    sm_manager_2d_skeleton_ = std::make_unique<SharedMemoryManager>(50003, sizeof(struct Skeleton2d));
    sm_manager_3d_skeleton_ = std::make_unique<SharedMemoryManager>(50004, sizeof(struct Skeleton3d));
    sm_manager_driver_status_ = std::make_unique<SharedMemoryManager>(50005, sizeof(struct DriverStatus));
}

void TransferManager::Initialize(){
    std::cout << __func__ << std::endl;
    sk_manager_->Initialize();
    mq_manager_->Initialize();
    sm_manager_2d_skeleton_->Initialize();
    sm_manager_3d_skeleton_->Initialize();
    sm_manager_driver_status_->Initialize();
}

void TransferManager::Get2DSkeleton(){
    std::cout << __func__ << std::endl;
    int data;
    sk_manager_->ReceiveData(&data, 4);
}

void TransferManager::Send2DSkeleton(int camid, float skeleton_2d[][2]){
    std::cout << __func__ << std::endl;
    struct Skeleton2d data;
    data.camid = camid;
    memcpy(data.body, skeleton_2d, sizeof(data.body));
    sm_manager_2d_skeleton_->SendData(&data, sizeof(data));
}

void TransferManager::Send3DSkeleton(float skeleton_3d[][3]){
    std::cout << __func__ << std::endl;
    struct Skeleton3d data;
    memcpy(data.body, skeleton_3d, sizeof(data.body));
    sm_manager_3d_skeleton_->SendData(&data, sizeof(data));
}

void TransferManager::SendDriverStatus(int driver_status){
    std::cout << __func__ << std::endl;
    struct DriverStatus data;
    data.status = driver_status;
    sm_manager_driver_status_->SendData(&data, sizeof(data));
}

void TransferManager::SendUiControl(int ui_control){
    std::cout << __func__ << std::endl;
    struct UiControl data;
    data.control = ui_control;
    mq_manager_->SendData(&data, sizeof(data));
}