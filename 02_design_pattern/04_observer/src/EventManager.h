#ifndef __EVENT_MANAGER_H_
#define __EVENT_MANAGER_H_

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <map>

#include "event/IEventHandler.h"

using namespace std;

enum class EventType : unsigned int { guds = 1, routine = 2 };

class EventManager {
private:
    std::map<EventType, std::set<IEventHandler*>> event_handlers;
public:
    void AddEventHandler(EventType type, IEventHandler* handler);
    void DelEventHandler(EventType type, IEventHandler* handler);
    void Notify(EventType type, int data);
};

void EventManager::AddEventHandler(EventType type, IEventHandler* handler) {
    if(event_handlers.find(type) == event_handlers.end()) {
        event_handlers.insert({type, {handler}});
        return;
    }
    auto typed_handlers = event_handlers.find(type);
    if(typed_handlers->second.find(handler) == typed_handlers->second.end()) {
        typed_handlers->second.insert(handler);
        event_handlers.insert({type, typed_handlers->second});
    }
}

void EventManager::DelEventHandler(EventType type, IEventHandler* handler) {
    if(event_handlers.find(type) == event_handlers.end()) {
        return;
    }
    auto typed_handlers = event_handlers.find(type);
    if(typed_handlers->second.find(handler) != typed_handlers->second.end()) {
        typed_handlers->second.erase(handler);
        event_handlers[type] = typed_handlers->second;
    }
}

void EventManager::Notify(EventType type, int data) {
    if(event_handlers.find(type) == event_handlers.end()) {
        return;
    }
    auto typed_handlers = event_handlers.find(type);

    for(auto p : typed_handlers->second) {
        if(p != nullptr) {
            p->execute(data);
        }
    }
}
#endif
