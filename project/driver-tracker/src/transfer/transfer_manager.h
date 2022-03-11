#ifndef TRANSFER_MANAGER_H_
#define TRANSFER_MANAGER_H_

#include <memory>

#include "transfer/transfer_interface.h"
#include "transfer/socket/socket_manager.h"
#include "transfer/messagequeue/messagequeue_manager.h"
#include "transfer/sharedmemory/sharedmemory_manager.h"

class TransferManager : public TransferInterface {
 public:
    TransferManager() = default;
    virtual ~TransferManager() = default;

    void Initialize();

    void Get2DSkeleton();
    void Send2DSkeleton(int camid, float skeleton_2d[][2]);
    void Send3DSkeleton(float skeleton_3d[][3]);
    void SendDriverStatus(int driver_status);
    void SendUiControl(int ui_control);

 private:
    std::unique_ptr<SocketManager> socket_manager_;
    std::unique_ptr<MessageQueueManager> messagequeue_manager_;
    std::unique_ptr<SharedMemoryManager> sharedmemory_manager_;
};

#endif
