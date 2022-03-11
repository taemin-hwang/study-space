#ifndef TRANSFER_MANAGER_H_
#define TRANSFER_MANAGER_H_

#include <memory>

#include "transfer/transfer_interface.h"
#include "transfer/socket/socket_manager.h"
#include "transfer/messagequeue/messagequeue_manager.h"
#include "transfer/sharedmemory/sharedmemory_manager.h"

class TransferManager : public TransferInterface {
 public:
    TransferManager();
    virtual ~TransferManager() = default;

    void Initialize();

    void Get2DSkeleton();
    void Send2DSkeleton(int camid, float skeleton_2d[][2]);
    void Send3DSkeleton(float skeleton_3d[][3]);
    void SendDriverStatus(int driver_status);
    void SendUiControl(int ui_control);

 private:
    std::unique_ptr<SocketManager> sk_manager_;
    std::unique_ptr<MessageQueueManager> mq_manager_;
    std::unique_ptr<SharedMemoryManager> sm_manager_2d_skeleton_;
    std::unique_ptr<SharedMemoryManager> sm_manager_3d_skeleton_;
    std::unique_ptr<SharedMemoryManager> sm_manager_driver_status_;
};

#endif
