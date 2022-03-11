#include "driver_tracker.h"
#include <chrono>
#include <thread>
#include <cstring>

#include "transfer/transfer_manager.h"

using namespace std::chrono_literals;

DriverTracker::DriverTracker() {
    std::cout << __func__ << std::endl;
    estimator_ = std::make_unique<Estimator>();
    transfer_ = std::make_unique<TransferManager>();
}

void DriverTracker::Initialize(){
    std::cout << __func__ << std::endl;
    //estimator_->Initialize();
    transfer_->Initialize();
}

void DriverTracker::Run(){
    std::cout << __func__ << std::endl;

    transfer_->Get2DSkeleton();

    int camid = 0;
    float skeleton_2d[11][2];
    float skeleton_3d[11][3];
    memset(skeleton_2d, 1, sizeof(skeleton_2d));
    memset(skeleton_3d, 1, sizeof(skeleton_3d));
    int driver_status = 0;
    int ui_control = 0;

    transfer_->Send2DSkeleton(camid, skeleton_2d);
    transfer_->Send3DSkeleton(skeleton_3d);
    transfer_->SendDriverStatus(driver_status);
    transfer_->SendUiControl(ui_control);

    int cnt = 0;
    while(true) {
        transfer_->SendUiControl(cnt++);
        transfer_->SendDriverStatus(100 + cnt++);
        std::this_thread::sleep_for(1000ms);
    }
}

void DriverTracker::Shutdown(){
    std::cout << __func__ << std::endl;

}

void DriverTracker::DriverHeatmapHandler() {
    std::cout << __func__ << std::endl;
}
