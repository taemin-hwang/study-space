#ifndef DRIVER_TRACKER_H_
#define DRIVER_TRACKER_H_

#include <iostream>
#include <memory>

#include "transfer/transfer_interface.h"
#include "estimator/estimator.h"

class DriverTracker {
 public:
    DriverTracker() = default;
    virtual ~DriverTracker() = default;

    void Initialize();
    void Run();
    void Shutdown();

 private:
    void DriverHeatmapHandler();

 private:
    std::unique_ptr<Estimator> estimator_;
    std::unique_ptr<TransferInterface> transfer_;
};

#endif
