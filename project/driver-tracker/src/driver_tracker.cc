#include "driver_tracker.h"
#include <chrono>
#include <thread>

#include "transfer/transfer_manager.h"

using namespace std::chrono_literals;

void DriverTracker::Initialize(){
    std::cout << __func__ << std::endl;
    estimator_ = std::make_unique<Estimator>();
    transfer_ = std::make_unique<TransferManager>();
}

void DriverTracker::Run(){
    std::cout << __func__ << std::endl;

    transfer_->Get2DSkeleton();

    int camid;
    float skeleton_2d[11][2];
    float skeleton_3d[11][3];
    int driver_status = 0;
    int ui_control = 0;

    transfer_->Send2DSkeleton(camid, skeleton_2d);
    transfer_->Send3DSkeleton(skeleton_3d);
    transfer_->SendDriverStatus(driver_status);
    transfer_->SendUiControl(ui_control);

    while(true) {

        std::this_thread::sleep_for(10ms);
    }
}

void DriverTracker::Shutdown(){
    std::cout << __func__ << std::endl;

}

void DriverTracker::DriverHeatmapHandler() {
    std::cout << __func__ << std::endl;
}
