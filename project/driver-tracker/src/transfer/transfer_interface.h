#ifndef TRANSFER_INTERFACE_H_
#define TRANSFER_INTERFACE_H_

#include <iostream>

class TransferInterface {
 public:
    TransferInterface() = default;
    virtual ~TransferInterface() = default;
    virtual void Initialize() = 0;

    virtual void Get2DSkeleton() = 0;
    virtual void Send2DSkeleton(int camid, float skeleton_2d[][2]) = 0;
    virtual void Send3DSkeleton(float skeleton_3d[][3]) = 0;
    virtual void SendDriverStatus(int driver_status) = 0;
    virtual void SendUiControl(int ui_control) = 0;
};

#endif
