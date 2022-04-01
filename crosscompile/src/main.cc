#include <iostream>
#include <memory>
#include "driver_tracker.h"

int main() {
    auto driver_tracker = std::make_unique<DriverTracker>();

    driver_tracker->Initialize();
    driver_tracker->Run();
    driver_tracker->Shutdown();

}
