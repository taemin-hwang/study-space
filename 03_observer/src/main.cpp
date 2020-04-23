#include <iostream>
#include <vector>
#include <memory>

#include "EventManager.h"
#include "event/GudsHandler.h"
#include "event/RoutineHandler.h"

using namespace std;

int main() {
    std::unique_ptr<EventManager> event_manager_ = std::make_unique<EventManager>();
    GudsHandler a;
    RoutineHandler b1(1), b2(2);

    // add subscriber
    event_manager_->AddEventHandler(EventType::guds, &a);
    event_manager_->AddEventHandler(EventType::routine, &b1);
    event_manager_->AddEventHandler(EventType::routine, &b2);

    // broadcast data to subscribers
    event_manager_->Notify(EventType::guds, 10);
    event_manager_->Notify(EventType::routine, 20);
}
