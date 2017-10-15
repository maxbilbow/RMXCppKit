//
//  RMXNotificationCenter.cpp
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//



#include "NotificationCenter.h"
#include <typeinfo>

#ifdef DEBUG_RMX_NOTIFICATION_CENTER
#define DEBUG_THIS true
#endif

using namespace rmx;


using namespace std;

static NotificationCenter * INSTANCE = nullptr;

NotificationCenter* NotificationCenter::getInstance() {
    return INSTANCE != nullptr ? INSTANCE : (INSTANCE = new NotificationCenter);
}

bool NotificationCenter::hasListener(EventListener * listener) {
    auto it = listeners.begin();

    do {
        if (*it == listener)
            return true;
    } while (it++ != this->listeners.end());

    return false;
}

void NotificationCenter::reset(EventType theEvent) {
    this->events[theEvent] = EVENT_STATUS_IDLE;
}
    
void NotificationCenter::addListener(EventListener * listener) {
    if (!this->hasListener(listener)) {
        this->listeners.push_back(listener);
    } else {
        cout << "\n !! Not Adding => Listeners already contain: " << listener << endl;
    }
}

EventListener * NotificationCenter::removeListener(EventListener * listener) {
    this->listeners.remove(listener);
    return listener;
}

EventStatus NotificationCenter::statusOf(EventType theEvent) {
    try {
        return this->events[theEvent];
    } catch (exception& e) {
        cout << typeid(this).name() << ": " << e.what() << ": setting new event as Idle" << endl;
        this->events[theEvent] = EVENT_STATUS_IDLE;
        return EVENT_STATUS_IDLE;
    }
}

bool NotificationCenter::isIdle(EventType theEvent) {
    return statusOf(std::move(theEvent)) == EVENT_STATUS_IDLE;
}

 bool NotificationCenter::isActive(EventType theEvent) {
    return statusOf(std::move(theEvent)) == EVENT_STATUS_ACTIVE;
}


void NotificationCenter::eventDidOccur(EventType theEvent, EventArgs o) {
    eventWillStart(theEvent,o);
    eventDidEnd(theEvent,o);
}


bool NotificationCenter::isComplete(EventType theEvent) {
    return statusOf(std::move(theEvent)) == EVENT_STATUS_COMPLETE;
}

bool NotificationCenter::didFail(EventType theEvent) {
    return statusOf(std::move(theEvent)) == EVENT_STATUS_FAILURE;
}


void NotificationCenter::eventWillStart(EventType theEvent, EventArgs o) {
    auto it = this->listeners.begin();
    do {
        (*it)->OnEventDidStart(theEvent, o);
    } while (it++ != this->listeners.end());
}

void NotificationCenter::eventDidEnd(EventType theEvent, EventArgs o) {
    auto it = this->listeners.begin();
    do {
        (*it)->OnEventDidEnd(theEvent, o);
    } while (it++ != this->listeners.end());
}

 void NotificationCenter::notifyListeners(string message, EventArgs args) {
     auto it = this->listeners.begin();
     do {
         (*it)->SendMessage(message, args);
     } while (it++ != this->listeners.end());
}

#ifdef DEBUG_THIS
#undef DEBUG_THIS
#endif


